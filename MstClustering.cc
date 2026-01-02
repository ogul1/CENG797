#include "MstClustering.h"

#include "inet/common/packet/Packet.h"
#include "inet/networklayer/common/L3AddressTag_m.h"
#include "inet/common/ProtocolTag_m.h"
#include "inet/networklayer/common/L3Tools.h"

namespace mstclustering {

Define_Module(MstClustering);

const char* MstClustering::clusterColors[] = {
    "#E63946",
    "#2A9D8F",
    "#E9C46A",
    "#264653",
    "#F4A261",
    "#6A0DAD",
    "#00CED1",
    "#FF69B4",
    "#32CD32",
    "#FFD700",
    "#4169E1",
    "#FF6347",
    "#20B2AA",
    "#DA70D6",
    "#00FA9A",
    "#FF4500"
};
const int MstClustering::numColors = 16;

void MstClustering::initialize(int stage)
{
    cSimpleModule::initialize(stage);
    
    if (stage == INITSTAGE_LOCAL) {
        helloInterval = par("helloInterval").doubleValue();
        mstUpdateInterval = par("mstUpdateInterval").doubleValue();
        clusterTimeout = par("clusterTimeout").doubleValue();
        maxClusterSize = par("maxClusterSize").intValue();
        communicationRange = par("communicationRange").doubleValueInUnit("m");
        EV_INFO << "Communication range set to: " << communicationRange << "m" << endl;
        edgeWeightAlpha = par("edgeWeightAlpha").doubleValue();
        edgeWeightBeta = par("edgeWeightBeta").doubleValue();
        edgeWeightGamma = par("edgeWeightGamma").doubleValue();
        enableDynamicMst = par("enableDynamicMst").boolValue();
        maxClusters = par("maxClusters").intValue();
        clusterThreshold = par("clusterThreshold").doubleValue();
        localPort = par("localPort").intValue();
        destPort = par("destPort").intValue();
        
        nodeId = getParentModule()->getIndex();
        myRole = ROLE_UNDECIDED;
        myClusterId = -1;
        myClusterHeadId = -1;
        myEnergy = 1.0;
        
        helloSeqNum = 0;
        topologySeqNum = 0;
        helloMessagesSent = 0;
        helloMessagesReceived = 0;
        topologyUpdatesSent = 0;
        topologyUpdatesReceived = 0;
        reClusteringCount = 0;
        
        clusterIdSignal = registerSignal("clusterId");
        clusterSizeSignal = registerSignal("clusterSize");
        clusterHeadSignal = registerSignal("isClusterHead");
        reClusteringSignal = registerSignal("reClusteringCount");
        controlOverheadSignal = registerSignal("controlOverhead");
        clusterStabilitySignal = registerSignal("clusterStability");
        numNeighborsSignal = registerSignal("numNeighbors");
        energySignal = registerSignal("energy");
        numClustersSignal = registerSignal("numClusters");
        mstEdgeCountSignal = registerSignal("mstEdgeCount");
        
        helloTimer = new cMessage("helloTimer");
        mstUpdateTimer = new cMessage("mstUpdateTimer");
        clusterCheckTimer = new cMessage("clusterCheckTimer");
        visualizationTimer = new cMessage("visualizationTimer");
        
        EV_INFO << "MST Clustering module initialized for node " << nodeId << endl;
    }
    else if (stage == INITSTAGE_APPLICATION_LAYER) {
        cModule *host = getParentModule();
        
        mobility = check_and_cast<IMobility*>(host->getSubmodule("mobility"));
        interfaceTable = getModuleFromPar<IInterfaceTable>(par("interfaceTableModule"), this);
        
        cModule *energyStorageModule = host->getSubmodule("energyStorage");
        if (energyStorageModule) {
            energyStorage = check_and_cast<IEpEnergyStorage*>(energyStorageModule);
        } else {
            energyStorage = nullptr;
            EV_WARN << "No energy storage module found, using default energy value" << endl;
        }
        
        socket.setOutputGate(gate("socketOut"));
        socket.bind(localPort);
        socket.setBroadcast(true);
        
        scheduleAt(simTime() + uniform(0, helloInterval), helloTimer);
        scheduleAt(simTime() + mstUpdateInterval + uniform(0, 1), mstUpdateTimer);
        scheduleAt(simTime() + clusterTimeout, clusterCheckTimer);
        scheduleAt(simTime() + 0.5, visualizationTimer);
        
        updatePosition();
        
        EV_INFO << "MST Clustering application layer initialized for node " << nodeId 
                << " at position " << myPosition << endl;
    }
}

void MstClustering::handleMessage(cMessage *msg)
{
    if (msg->isSelfMessage()) {
        handleSelfMessage(msg);
    }
    else if (msg->arrivedOn("socketIn")) {
        Packet *packet = check_and_cast<Packet*>(msg);
        handleUdpPacket(packet);
    }
    else {
        EV_WARN << "Received unknown message: " << msg->getName() << endl;
        delete msg;
    }
}

void MstClustering::handleSelfMessage(cMessage *msg)
{
    if (msg == helloTimer) {
        sendHello();
        checkNeighborTimeout();
        scheduleAt(simTime() + helloInterval, helloTimer);
    }
    else if (msg == mstUpdateTimer) {
        updatePosition();
        updateEnergy();
        
        if (enableDynamicMst) {
            updateMstIncremental();
        } else {
            buildMst();
        }
        
        formClusters();
        recordStatistics();
        
        scheduleAt(simTime() + mstUpdateInterval, mstUpdateTimer);
    }
    else if (msg == clusterCheckTimer) {
        if (!isClusterStable()) {
            handleReClusteringNeeded();
        }
        scheduleAt(simTime() + clusterTimeout, clusterCheckTimer);
    }
    else if (msg == visualizationTimer) {
        updateVisualization();
        scheduleAt(simTime() + 0.2, visualizationTimer);
    }
    else {
        EV_WARN << "Unknown self message: " << msg->getName() << endl;
    }
}

void MstClustering::handleUdpPacket(Packet *packet)
{
    auto chunk = packet->peekAtFront<Chunk>();
    
    if (auto hello = dynamicPtrCast<const HelloPacket>(chunk)) {
        helloMessagesReceived++;
        processHelloPacket(const_cast<HelloPacket*>(hello.get()));
    }
    else if (auto topologyUpdate = dynamicPtrCast<const TopologyUpdatePacket>(chunk)) {
        topologyUpdatesReceived++;
        processTopologyUpdate(const_cast<TopologyUpdatePacket*>(topologyUpdate.get()));
    }
    else if (auto clusterJoin = dynamicPtrCast<const ClusterJoinPacket>(chunk)) {
        processClusterJoin(const_cast<ClusterJoinPacket*>(clusterJoin.get()));
    }
    else if (auto clusterHead = dynamicPtrCast<const ClusterHeadPacket>(chunk)) {
        processClusterHead(const_cast<ClusterHeadPacket*>(clusterHead.get()));
    }
    else if (auto edgeInfo = dynamicPtrCast<const EdgeInfoPacket>(chunk)) {
        processEdgeInfo(const_cast<EdgeInfoPacket*>(edgeInfo.get()));
    }
    
    delete packet;
}

void MstClustering::sendHello()
{
    updatePosition();
    updateEnergy();
    
    EV_INFO << "Node " << nodeId << " at position (" << myPosition.x << ", " << myPosition.y 
            << "), communicationRange = " << communicationRange << endl;
    
    neighbors.clear();
    
    cModule *network = getParentModule()->getParentModule();
    
    for (cModule::SubmoduleIterator it(network); !it.end(); ++it) {
        cModule *otherNode = *it;
        
        if (!otherNode->isName("node")) continue;
        
        int otherNodeId = otherNode->getIndex();
        if (otherNodeId == nodeId) continue;
        
        cModule *otherMobilityModule = otherNode->getSubmodule("mobility");
        if (!otherMobilityModule) {
            EV_WARN << "Node " << nodeId << " could not find mobility in node[" << otherNodeId << "]" << endl;
            continue;
        }
        
        IMobility *otherMobility = dynamic_cast<IMobility*>(otherMobilityModule);
        if (!otherMobility) {
            EV_WARN << "Node " << nodeId << ": mobility module is not IMobility" << endl;
            continue;
        }
        
        Coord otherPos = otherMobility->getCurrentPosition();
        
        double distance = myPosition.distance(otherPos);
        
        if (distance <= communicationRange) {
            NeighborInfo& neighbor = neighbors[otherNodeId];
            neighbor.nodeId = otherNodeId;
            neighbor.position = otherPos;
            neighbor.distance = distance;
            neighbor.lastHeard = simTime();
            neighbor.missedHellos = 0;
            neighbor.linkQuality = 1.0 - (distance / communicationRange);
            neighbor.energy = 1.0;
            
            cModule *otherClustering = otherNode->getSubmodule("mstClustering");
            if (otherClustering) {
                MstClustering *other = dynamic_cast<MstClustering*>(otherClustering);
                if (other) {
                    neighbor.clusterId = other->myClusterId;
                    neighbor.clusterHeadId = other->myClusterHeadId;
                    neighbor.energy = other->myEnergy;
                }
            }
            
            EV_INFO << "Node " << nodeId << " ADDED neighbor " << otherNodeId 
                    << " at distance " << distance << "m" << endl;
        }
    }
    
    helloMessagesSent++;
    emit(controlOverheadSignal, (long)1);
    emit(numNeighborsSignal, (long)neighbors.size());
    
    EV_INFO << "Node " << nodeId << " has " << neighbors.size() << " neighbors total" << endl;
}

void MstClustering::processHelloPacket(HelloPacket *hello)
{
    int senderId = hello->getNodeId();
    
    if (senderId == nodeId) return;
    
    NeighborInfo& neighbor = neighbors[senderId];
    neighbor.nodeId = senderId;
    neighbor.position.x = hello->getPosX();
    neighbor.position.y = hello->getPosY();
    neighbor.position.z = hello->getPosZ();
    neighbor.energy = hello->getEnergy();
    neighbor.clusterId = hello->getClusterId();
    neighbor.clusterHeadId = hello->getClusterHeadId();
    neighbor.nodeRole = hello->getNodeRole();
    neighbor.lastHeard = simTime();
    neighbor.distance = getDistanceTo(neighbor.position);
    neighbor.missedHellos = 0;
    
    if (neighbor.distance < communicationRange) {
        neighbor.linkQuality = 1.0 - (neighbor.distance / communicationRange);
    } else {
        neighbor.linkQuality = 0.0;
    }
    
    double weight = calculateEdgeWeight(neighbor);
    
    bool edgeExists = false;
    for (auto& edge : allEdges) {
        if ((edge.node1 == nodeId && edge.node2 == senderId) ||
            (edge.node1 == senderId && edge.node2 == nodeId)) {
            edge.weight = weight;
            edge.lastUpdate = simTime();
            edgeExists = true;
            break;
        }
    }
    
    if (!edgeExists && neighbor.distance <= communicationRange) {
        MstEdge newEdge(std::min(nodeId, senderId), std::max(nodeId, senderId), weight);
        newEdge.lastUpdate = simTime();
        allEdges.push_back(newEdge);
        
        if (enableDynamicMst) {
            updateMstIncremental(senderId, -1);
        }
    }
    
    emit(numNeighborsSignal, (long)neighbors.size());
    
    EV_INFO << "Node " << nodeId << " received hello from node " << senderId 
            << " at distance " << neighbor.distance 
            << " (within range: " << (neighbor.distance <= communicationRange ? "YES" : "NO") << ")" << endl;
}

void MstClustering::processTopologyUpdate(TopologyUpdatePacket *update)
{
    int srcId = update->getSourceId();
    int dstId = update->getDestId();
    double weight = update->getWeight();
    bool isActive = update->isActive();
    
    for (auto& edge : allEdges) {
        if ((edge.node1 == srcId && edge.node2 == dstId) ||
            (edge.node1 == dstId && edge.node2 == srcId)) {
            edge.weight = weight;
            edge.inMst = isActive;
            edge.lastUpdate = simTime();
            break;
        }
    }
}

void MstClustering::processClusterJoin(ClusterJoinPacket *join)
{
    int joinNodeId = join->getNodeId();
    int clusterId = join->getClusterId();
    int chId = join->getClusterHeadId();
    
    if (neighbors.find(joinNodeId) != neighbors.end()) {
        neighbors[joinNodeId].clusterId = clusterId;
        neighbors[joinNodeId].clusterHeadId = chId;
    }
    
    if (myRole == ROLE_CLUSTER_HEAD && myClusterId == clusterId) {
        clusters[clusterId].members.insert(joinNodeId);
        EV_INFO << "Node " << joinNodeId << " joined cluster " << clusterId << endl;
    }
}

void MstClustering::processClusterHead(ClusterHeadPacket *chPacket)
{
    int clusterId = chPacket->getClusterId();
    int chId = chPacket->getClusterHeadId();
    
    if (myClusterId == clusterId && myClusterHeadId != chId) {
        myClusterHeadId = chId;
        
        if (chId == nodeId) {
            myRole = ROLE_CLUSTER_HEAD;
            clusterHeadStartTime = simTime();
        } else {
            myRole = ROLE_CLUSTER_MEMBER;
        }
        
        updateNodeColor();
    }
}

void MstClustering::processEdgeInfo(EdgeInfoPacket *edgeInfo)
{
    int srcId = edgeInfo->getSourceId();
    int dstId = edgeInfo->getDestId();
    double weight = edgeInfo->getWeight();
    
    bool found = false;
    for (auto& edge : allEdges) {
        if ((edge.node1 == srcId && edge.node2 == dstId) ||
            (edge.node1 == dstId && edge.node2 == srcId)) {
            found = true;
            break;
        }
    }
    
    if (!found) {
        MstEdge newEdge(std::min(srcId, dstId), std::max(srcId, dstId), weight);
        newEdge.lastUpdate = simTime();
        allEdges.push_back(newEdge);
    }
}

void MstClustering::checkNeighborTimeout()
{
    simtime_t now = simTime();
    std::vector<int> timedOut;
    
    for (auto& pair : neighbors) {
        pair.second.missedHellos++;
        if (now - pair.second.lastHeard > clusterTimeout) {
            timedOut.push_back(pair.first);
        }
    }
    
    for (int id : timedOut) {
        EV_INFO << "Node " << nodeId << ": Neighbor " << id << " timed out" << endl;
        neighbors.erase(id);
        
        allEdges.erase(
            std::remove_if(allEdges.begin(), allEdges.end(),
                [id](const MstEdge& e) { return e.node1 == id || e.node2 == id; }),
            allEdges.end()
        );
        
        if (enableDynamicMst) {
            updateMstIncremental(-1, id);
        }
    }
}

double MstClustering::calculateEdgeWeight(const NeighborInfo& neighbor)
{
    double distanceWeight = neighbor.distance / communicationRange;
    double energyWeight = 1.0 - ((myEnergy + neighbor.energy) / 2.0);
    double linkWeight = 1.0 - neighbor.linkQuality;
    
    return edgeWeightAlpha * distanceWeight + 
           edgeWeightBeta * energyWeight + 
           edgeWeightGamma * linkWeight;
}

void MstClustering::buildMst()
{
    if (allEdges.empty()) return;
    
    mstEdges.clear();
    unionFind.clear();
    
    std::vector<MstEdge> sortedEdges = allEdges;
    std::sort(sortedEdges.begin(), sortedEdges.end());
    
    unionFind.makeSet(nodeId);
    for (const auto& neighbor : neighbors) {
        unionFind.makeSet(neighbor.first);
    }
    
    for (auto& edge : sortedEdges) {
        if (unionFind.find(edge.node1) != unionFind.find(edge.node2)) {
            unionFind.unite(edge.node1, edge.node2);
            edge.inMst = true;
            mstEdges.push_back(edge);
        }
    }
    
    for (auto& edge : allEdges) {
        edge.inMst = false;
        for (const auto& mstEdge : mstEdges) {
            if (edge == mstEdge) {
                edge.inMst = true;
                break;
            }
        }
    }
    
    emit(mstEdgeCountSignal, (long)mstEdges.size());
    
    EV_INFO << "Node " << nodeId << " built MST with " << mstEdges.size() << " edges" << endl;
}

void MstClustering::updateMstIncremental(int addedNode, int removedNode)
{
    if (removedNode >= 0) {
        mstEdges.erase(
            std::remove_if(mstEdges.begin(), mstEdges.end(),
                [removedNode](const MstEdge& e) { 
                    return e.node1 == removedNode || e.node2 == removedNode; 
                }),
            mstEdges.end()
        );
        
        buildMst();
    }
    else if (addedNode >= 0) {
        MstEdge* minEdge = nullptr;
        double minWeight = std::numeric_limits<double>::max();
        
        for (auto& edge : allEdges) {
            if ((edge.node1 == addedNode || edge.node2 == addedNode) &&
                edge.weight < minWeight) {
                int otherNode = (edge.node1 == addedNode) ? edge.node2 : edge.node1;
                
                bool otherInMst = false;
                for (const auto& mstEdge : mstEdges) {
                    if (mstEdge.node1 == otherNode || mstEdge.node2 == otherNode) {
                        otherInMst = true;
                        break;
                    }
                }
                
                if (otherInMst || nodeId == otherNode) {
                    minWeight = edge.weight;
                    minEdge = &edge;
                }
            }
        }
        
        if (minEdge != nullptr) {
            minEdge->inMst = true;
            mstEdges.push_back(*minEdge);
        }
    }
    else {
        bool needsRebuild = false;
        
        for (auto& edge : allEdges) {
            if (edge.inMst) {
                for (const auto& mstEdge : mstEdges) {
                    if (edge == mstEdge && edge.weight > mstEdge.weight * 1.5) {
                        needsRebuild = true;
                        break;
                    }
                }
            }
        }
        
        if (needsRebuild) {
            buildMst();
        }
    }
    
    emit(mstEdgeCountSignal, (long)mstEdges.size());
}

void MstClustering::formClusters()
{
    EV_INFO << "Node " << nodeId << " forming clusters. Neighbors: " << neighbors.size() << endl;
    
    if (neighbors.empty()) {
        myClusterId = nodeId;
        myClusterHeadId = nodeId;
        myRole = ROLE_CLUSTER_HEAD;
        clusterHeadStartTime = simTime();
        updateNodeColor();
        EV_INFO << "Node " << nodeId << " has no neighbors, forming singleton cluster" << endl;
        return;
    }
    
    int minId = nodeId;
    for (const auto& pair : neighbors) {
        if (pair.first < minId) {
            minId = pair.first;
        }
    }
    
    myClusterId = minId;
    myClusterHeadId = minId;
    
    if (myClusterId == nodeId) {
        if (myRole != ROLE_CLUSTER_HEAD) {
            myRole = ROLE_CLUSTER_HEAD;
            clusterHeadStartTime = simTime();
        }
    } else {
        myRole = ROLE_CLUSTER_MEMBER;
    }
    
    ClusterInfo& cluster = clusters[myClusterId];
    cluster.clusterId = myClusterId;
    cluster.clusterHeadId = myClusterId;
    cluster.members.clear();
    cluster.members.insert(nodeId);
    
    for (const auto& pair : neighbors) {
        cluster.members.insert(pair.first);
    }
    
    EV_INFO << "Node " << nodeId << " assigned to cluster " << myClusterId 
            << " (role: " << (myRole == ROLE_CLUSTER_HEAD ? "HEAD" : "MEMBER") 
            << ", neighbors: " << neighbors.size() << ")" << endl;
    
    updateNodeColor();
}

void MstClustering::breakMstForClusters()
{
    if (maxClusters <= 1 || mstEdges.size() < 2) {
        myClusterId = 0;
        return;
    }
    
    std::vector<MstEdge> sortedMstEdges = mstEdges;
    std::sort(sortedMstEdges.begin(), sortedMstEdges.end(),
        [](const MstEdge& a, const MstEdge& b) { return a.weight > b.weight; });
    
    int edgesToBreak = std::min(maxClusters - 1, (int)sortedMstEdges.size());
    
    for (size_t i = 0; i < sortedMstEdges.size(); i++) {
        if (sortedMstEdges[i].weight < clusterThreshold) {
            edgesToBreak = std::min(edgesToBreak, (int)i);
            break;
        }
    }
    
    std::set<std::pair<int,int>> brokenEdges;
    for (int i = 0; i < edgesToBreak; i++) {
        brokenEdges.insert({sortedMstEdges[i].node1, sortedMstEdges[i].node2});
    }
    
    UnionFind clusterUF;
    clusterUF.makeSet(nodeId);
    for (const auto& neighbor : neighbors) {
        clusterUF.makeSet(neighbor.first);
    }
    
    for (const auto& edge : mstEdges) {
        if (brokenEdges.find({edge.node1, edge.node2}) == brokenEdges.end() &&
            brokenEdges.find({edge.node2, edge.node1}) == brokenEdges.end()) {
            clusterUF.unite(edge.node1, edge.node2);
        }
    }
    
    myClusterId = clusterUF.find(nodeId);
    
    ClusterInfo& cluster = clusters[myClusterId];
    cluster.clusterId = myClusterId;
    cluster.members = clusterUF.getComponent(nodeId);
    
    EV_INFO << "Node " << nodeId << " assigned to cluster " << myClusterId 
            << " with " << cluster.members.size() << " members" << endl;
}

void MstClustering::electClusterHead()
{
    if (myClusterId < 0) return;
    
    ClusterInfo& cluster = clusters[myClusterId];
    
    int bestCandidate = nodeId;
    double bestScore = myEnergy * 0.7 + (neighbors.size() / 10.0) * 0.3;
    
    for (int memberId : cluster.members) {
        if (memberId == nodeId) continue;
        
        auto it = neighbors.find(memberId);
        if (it != neighbors.end()) {
            double score = it->second.energy * 0.7 + (neighbors.size() / 10.0) * 0.3;
            if (score > bestScore || (score == bestScore && memberId < bestCandidate)) {
                bestScore = score;
                bestCandidate = memberId;
            }
        }
    }
    
    myClusterHeadId = bestCandidate;
    
    if (myClusterHeadId == nodeId) {
        if (myRole != ROLE_CLUSTER_HEAD) {
            myRole = ROLE_CLUSTER_HEAD;
            clusterHeadStartTime = simTime();
            announceClusterHead();
        }
    } else {
        myRole = ROLE_CLUSTER_MEMBER;
    }
    
    cluster.clusterHeadId = myClusterHeadId;
    
    EV_INFO << "Node " << nodeId << " in cluster " << myClusterId 
            << " - cluster head is " << myClusterHeadId << endl;
}

void MstClustering::joinCluster(int clusterId, int clusterHeadId)
{
    if (myClusterId == clusterId) return;
    
    myClusterId = clusterId;
    myClusterHeadId = clusterHeadId;
    myRole = ROLE_CLUSTER_MEMBER;
    
    auto joinPacket = makeShared<ClusterJoinPacket>();
    joinPacket->setNodeId(nodeId);
    joinPacket->setClusterId(clusterId);
    joinPacket->setClusterHeadId(clusterHeadId);
    joinPacket->setEnergy(myEnergy);
    joinPacket->setSequenceNumber(++topologySeqNum);
    joinPacket->setChunkLength(B(32));
    
    Packet *packet = new Packet("ClusterJoin");
    packet->insertAtFront(joinPacket);
    broadcastPacket(packet);
    
    updateNodeColor();
}

void MstClustering::leaveCluster()
{
    if (myClusterId < 0) return;
    
    clusters[myClusterId].members.erase(nodeId);
    
    myClusterId = -1;
    myClusterHeadId = -1;
    myRole = ROLE_UNDECIDED;
    
    updateNodeColor();
}

void MstClustering::announceClusterHead()
{
    auto chPacket = makeShared<ClusterHeadPacket>();
    chPacket->setClusterId(myClusterId);
    chPacket->setClusterHeadId(nodeId);
    chPacket->setMemberCount(clusters[myClusterId].members.size());
    chPacket->setAvgEnergy(myEnergy);
    chPacket->setSequenceNumber(++topologySeqNum);
    chPacket->setChunkLength(B(32));
    
    Packet *packet = new Packet("ClusterHead");
    packet->insertAtFront(chPacket);
    broadcastPacket(packet);
    
    emit(controlOverheadSignal, (long)1);
}

void MstClustering::handleReClusteringNeeded()
{
    EV_INFO << "Node " << nodeId << " triggering re-clustering due to instability" << endl;
    
    buildMst();
    formClusters();
}

bool MstClustering::isClusterStable()
{
    if (myClusterId < 0) return false;
    
    if (myClusterHeadId != nodeId) {
        auto it = neighbors.find(myClusterHeadId);
        if (it == neighbors.end() || 
            simTime() - it->second.lastHeard > helloInterval * 3) {
            return false;
        }
    }
    
    int changedNeighbors = 0;
    for (const auto& pair : neighbors) {
        if (pair.second.clusterId != myClusterId && 
            pair.second.clusterId >= 0) {
            changedNeighbors++;
        }
    }
    
    return changedNeighbors < (int)(neighbors.size() * 0.5);
}

void MstClustering::updatePosition()
{
    if (mobility) {
        myPosition = mobility->getCurrentPosition();
    }
}

void MstClustering::updateEnergy()
{
    if (energyStorage) {
        J capacity = energyStorage->getNominalEnergyCapacity();
        J residual = energyStorage->getResidualEnergyCapacity();
        if (capacity.get() > 0) {
            myEnergy = residual.get() / capacity.get();
        }
    }
    emit(energySignal, myEnergy);
}

double MstClustering::getDistanceTo(const Coord& pos)
{
    return myPosition.distance(pos);
}

void MstClustering::updateVisualization()
{
    updateNodeColor();
    drawMstEdges();
}

void MstClustering::updateNodeColor()
{
    cModule *host = getParentModule();
    if (!host) return;
    
    const char* color = getClusterColor(myClusterId);
    
    char displayStr[128];
    const char* roleStr = (myRole == ROLE_CLUSTER_HEAD) ? "CH" : 
                          (myRole == ROLE_GATEWAY) ? "GW" : 
                          (myRole == ROLE_CLUSTER_MEMBER) ? "M" : "?";
    
    host->getDisplayString().setTagArg("b", 0, "40");
    host->getDisplayString().setTagArg("b", 1, "40");
    host->getDisplayString().setTagArg("b", 2, "oval");
    host->getDisplayString().setTagArg("b", 3, color);
    host->getDisplayString().setTagArg("b", 4, color);
    host->getDisplayString().setTagArg("b", 5, "2");
    
    snprintf(displayStr, sizeof(displayStr), "C%d %s E:%.0f%%",
             myClusterId, roleStr, myEnergy * 100);
    host->getDisplayString().setTagArg("t", 0, displayStr);
    
    if (myRole == ROLE_CLUSTER_HEAD) {
        host->getDisplayString().setTagArg("is", 0, "l");
    } else {
        host->getDisplayString().setTagArg("is", 0, "s");
    }
}

void MstClustering::drawMstEdges()
{
    clearMstEdges();
    
    cModule *network = getParentModule()->getParentModule();
    cCanvas *canvas = network->getCanvas();
    
    for (const auto& edge : mstEdges) {
        if (edge.node1 != nodeId && edge.node2 != nodeId) continue;
        
        int otherNode = (edge.node1 == nodeId) ? edge.node2 : edge.node1;
        
        char moduleName[32];
        snprintf(moduleName, sizeof(moduleName), "node[%d]", otherNode);
        cModule *otherModule = network->getSubmodule(moduleName);
        if (!otherModule) continue;
        
        char lineName[64];
        snprintf(lineName, sizeof(lineName), "mstEdge_%d_%d", 
                 std::min(nodeId, otherNode), std::max(nodeId, otherNode));
        
        cLineFigure *line = dynamic_cast<cLineFigure*>(canvas->getFigure(lineName));
        if (!line) {
            line = new cLineFigure(lineName);
            line->setLineWidth(2);
            line->setLineOpacity(0.6);
            line->setZIndex(-1);
            canvas->addFigure(line);
        }
        
        cDisplayString& myDs = getParentModule()->getDisplayString();
        cDisplayString& otherDs = otherModule->getDisplayString();
        
        double x1 = atof(myDs.getTagArg("p", 0));
        double y1 = atof(myDs.getTagArg("p", 1));
        double x2 = atof(otherDs.getTagArg("p", 0));
        double y2 = atof(otherDs.getTagArg("p", 1));
        
        line->setStart(cFigure::Point(x1, y1));
        line->setEnd(cFigure::Point(x2, y2));
        
        const char* color = getClusterColor(myClusterId);
        line->setLineColor(cFigure::parseColor(color));
    }
}

void MstClustering::clearMstEdges()
{
    cModule *network = getParentModule()->getParentModule();
    cCanvas *canvas = network->getCanvas();
    
    std::vector<cFigure*> toRemove;
    for (int i = 0; i < canvas->getNumFigures(); i++) {
        cFigure *fig = canvas->getFigure(i);
        std::string name = fig->getName();
        if (name.find("mstEdge_") == 0) {
            int n1, n2;
            if (sscanf(name.c_str(), "mstEdge_%d_%d", &n1, &n2) == 2) {
                if (n1 == nodeId || n2 == nodeId) {
                    toRemove.push_back(fig);
                }
            }
        }
    }
    
    for (cFigure* fig : toRemove) {
        canvas->removeFigure(fig);
        delete fig;
    }
}

void MstClustering::broadcastPacket(Packet *packet)
{
    socket.sendTo(packet, Ipv4Address::ALLONES_ADDRESS, destPort);
}

void MstClustering::sendToNeighbor(int neighborId, Packet *packet)
{
    broadcastPacket(packet);
}

void MstClustering::recordStatistics()
{
    emit(clusterIdSignal, (long)myClusterId);
    emit(clusterHeadSignal, (long)(myRole == ROLE_CLUSTER_HEAD ? 1 : 0));
    
    if (myClusterId >= 0 && clusters.find(myClusterId) != clusters.end()) {
        emit(clusterSizeSignal, (long)clusters[myClusterId].members.size());
    }
    
    std::set<int> uniqueClusters;
    uniqueClusters.insert(myClusterId);
    for (const auto& pair : neighbors) {
        if (pair.second.clusterId >= 0) {
            uniqueClusters.insert(pair.second.clusterId);
        }
    }
    emit(numClustersSignal, (long)uniqueClusters.size());
    
    if (nodeId == 0) {
        updateNetworkStatistics();
    }
    
    if (myRole == ROLE_CLUSTER_HEAD && clusterHeadStartTime > 0) {
        emit(clusterStabilitySignal, (simTime() - clusterHeadStartTime).dbl());
    }
}

const char* MstClustering::getClusterColor(int clusterId)
{
    if (clusterId < 0) return "#808080";
    return clusterColors[clusterId % numColors];
}

void MstClustering::updateNetworkStatistics()
{
    cModule *network = getParentModule()->getParentModule();
    cCanvas *canvas = network->getCanvas();
    
    std::set<int> allClusters;
    std::map<int, int> clusterSizes;
    int totalNodes = 0;
    
    for (cModule::SubmoduleIterator it(network); !it.end(); ++it) {
        cModule *node = *it;
        if (!node->isName("node")) continue;
        
        cModule *clusteringModule = node->getSubmodule("mstClustering");
        if (!clusteringModule) continue;
        
        MstClustering *clustering = dynamic_cast<MstClustering*>(clusteringModule);
        if (!clustering) continue;
        
        totalNodes++;
        int clusterId = clustering->myClusterId;
        if (clusterId >= 0) {
            allClusters.insert(clusterId);
            clusterSizes[clusterId]++;
        }
    }
    
    double avgClusterSize = 0;
    if (!allClusters.empty()) {
        avgClusterSize = (double)totalNodes / allClusters.size();
    }
    
    cFigure *numClustersFig = canvas->getFigure("numClustersText");
    if (numClustersFig) {
        cTextFigure *textFig = dynamic_cast<cTextFigure*>(numClustersFig);
        if (textFig) {
            char buf[64];
            snprintf(buf, sizeof(buf), "Active Clusters: %d", (int)allClusters.size());
            textFig->setText(buf);
        }
    }
    
    cFigure *avgSizeFig = canvas->getFigure("avgClusterSizeText");
    if (avgSizeFig) {
        cTextFigure *textFig = dynamic_cast<cTextFigure*>(avgSizeFig);
        if (textFig) {
            char buf[64];
            snprintf(buf, sizeof(buf), "Avg Cluster Size: %.1f", avgClusterSize);
            textFig->setText(buf);
        }
    }
}

void MstClustering::finish()
{
    cancelAndDelete(helloTimer);
    cancelAndDelete(mstUpdateTimer);
    cancelAndDelete(clusterCheckTimer);
    cancelAndDelete(visualizationTimer);
    
    clearMstEdges();
    
    EV_INFO << "MST Clustering node " << nodeId << " finished:" << endl;
    EV_INFO << "  - Final cluster ID: " << myClusterId << endl;
    EV_INFO << "  - Final role: " << (myRole == ROLE_CLUSTER_HEAD ? "Cluster Head" : 
                                       myRole == ROLE_GATEWAY ? "Gateway" : "Member") << endl;
    EV_INFO << "  - Hello messages sent: " << helloMessagesSent << endl;
    EV_INFO << "  - Hello messages received: " << helloMessagesReceived << endl;
    EV_INFO << "  - Re-clustering count: " << reClusteringCount << endl;
    EV_INFO << "  - Final neighbors: " << neighbors.size() << endl;
    EV_INFO << "  - MST edges: " << mstEdges.size() << endl;
}

}
