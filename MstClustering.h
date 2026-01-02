#ifndef __MST_CLUSTERING_H
#define __MST_CLUSTERING_H

#include <omnetpp.h>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <algorithm>

#include "inet/common/INETDefs.h"
#include "inet/common/ModuleAccess.h"
#include "inet/common/geometry/common/Coord.h"
#include "inet/mobility/contract/IMobility.h"
#include "inet/networklayer/common/L3AddressResolver.h"
#include "inet/networklayer/contract/IInterfaceTable.h"
#include "inet/transportlayer/contract/udp/UdpSocket.h"
#include "inet/power/contract/IEpEnergyStorage.h"

#include "MstClusteringPacket_m.h"

using namespace inet::power;

using namespace omnetpp;
using namespace inet;

namespace mstclustering {

class MstClustering;

struct MstEdge {
    int node1;
    int node2;
    double weight;
    bool inMst;
    simtime_t lastUpdate;
    
    MstEdge() : node1(-1), node2(-1), weight(0), inMst(false) {}
    MstEdge(int n1, int n2, double w) : node1(n1), node2(n2), weight(w), inMst(false) {}
    
    bool operator<(const MstEdge& other) const {
        return weight < other.weight;
    }
    
    bool operator==(const MstEdge& other) const {
        return (node1 == other.node1 && node2 == other.node2) ||
               (node1 == other.node2 && node2 == other.node1);
    }
};

struct NeighborInfo {
    int nodeId;
    Coord position;
    double energy;
    int clusterId;
    int clusterHeadId;
    int nodeRole;
    simtime_t lastHeard;
    double distance;
    double linkQuality;
    int missedHellos;
    
    NeighborInfo() : nodeId(-1), energy(1.0), clusterId(-1), clusterHeadId(-1),
                     nodeRole(0), distance(0), linkQuality(1.0), missedHellos(0) {}
};

struct ClusterInfo {
    int clusterId;
    int clusterHeadId;
    std::set<int> members;
    double avgEnergy;
    simtime_t formationTime;
    int reClusterCount;
    
    ClusterInfo() : clusterId(-1), clusterHeadId(-1), avgEnergy(1.0), reClusterCount(0) {}
};

class UnionFind {
private:
    std::map<int, int> parent;
    std::map<int, int> rank;
    
public:
    void makeSet(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
        }
    }
    
    int find(int x) {
        if (parent.find(x) == parent.end()) {
            makeSet(x);
        }
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    bool unite(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return false;
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
        return true;
    }
    
    void clear() {
        parent.clear();
        rank.clear();
    }
    
    std::set<int> getComponent(int x) {
        std::set<int> component;
        int root = find(x);
        for (auto& p : parent) {
            if (find(p.first) == root) {
                component.insert(p.first);
            }
        }
        return component;
    }
};

class MstClustering : public cSimpleModule
{
protected:
    int nodeId;
    double helloInterval;
    double mstUpdateInterval;
    double clusterTimeout;
    int maxClusterSize;
    double communicationRange;
    double edgeWeightAlpha;
    double edgeWeightBeta;
    double edgeWeightGamma;
    bool enableDynamicMst;
    int maxClusters;
    double clusterThreshold;
    
    NodeRole myRole;
    int myClusterId;
    int myClusterHeadId;
    double myEnergy;
    Coord myPosition;
    
    std::map<int, NeighborInfo> neighbors;
    std::vector<MstEdge> allEdges;
    std::vector<MstEdge> mstEdges;
    std::map<int, ClusterInfo> clusters;
    UnionFind unionFind;
    
    int helloSeqNum;
    int topologySeqNum;
    
    cMessage *helloTimer;
    cMessage *mstUpdateTimer;
    cMessage *clusterCheckTimer;
    cMessage *visualizationTimer;
    
    simsignal_t clusterIdSignal;
    simsignal_t clusterSizeSignal;
    simsignal_t clusterHeadSignal;
    simsignal_t reClusteringSignal;
    simsignal_t controlOverheadSignal;
    simsignal_t clusterStabilitySignal;
    simsignal_t numNeighborsSignal;
    simsignal_t energySignal;
    simsignal_t numClustersSignal;
    simsignal_t mstEdgeCountSignal;
    
    long helloMessagesSent;
    long helloMessagesReceived;
    long topologyUpdatesSent;
    long topologyUpdatesReceived;
    long reClusteringCount;
    simtime_t clusterHeadStartTime;
    
    UdpSocket socket;
    int localPort;
    int destPort;
    
    IMobility *mobility;
    IInterfaceTable *interfaceTable;
    IEpEnergyStorage *energyStorage;
    
    static const char* clusterColors[];
    static const int numColors;
    
protected:
    virtual int numInitStages() const override { return NUM_INIT_STAGES; }
    virtual void initialize(int stage) override;
    virtual void handleMessage(cMessage *msg) override;
    virtual void finish() override;
    
    void handleSelfMessage(cMessage *msg);
    void handleUdpPacket(Packet *packet);
    void processHelloPacket(HelloPacket *hello);
    void processTopologyUpdate(TopologyUpdatePacket *update);
    void processClusterJoin(ClusterJoinPacket *join);
    void processClusterHead(ClusterHeadPacket *chPacket);
    void processEdgeInfo(EdgeInfoPacket *edgeInfo);
    
    void sendHello();
    void checkNeighborTimeout();
    
    void buildMst();
    void updateMstIncremental(int addedNode = -1, int removedNode = -1);
    void addEdgeToMst(const MstEdge& edge);
    void removeEdgeFromMst(int node1, int node2);
    double calculateEdgeWeight(const NeighborInfo& neighbor);
    void formClusters();
    void breakMstForClusters();
    
    void electClusterHead();
    void joinCluster(int clusterId, int clusterHeadId);
    void leaveCluster();
    void announceClusterHead();
    void handleReClusteringNeeded();
    bool isClusterStable();
    
    void updatePosition();
    void updateEnergy();
    double getDistanceTo(const Coord& pos);
    
    void updateVisualization();
    void updateNodeColor();
    void drawMstEdges();
    void clearMstEdges();
    
    void broadcastPacket(Packet *packet);
    void sendToNeighbor(int neighborId, Packet *packet);
    void recordStatistics();
    void updateNetworkStatistics();
    int getNodeIdFromAddress(const L3Address& addr);
    const char* getClusterColor(int clusterId);
};

}

#endif
