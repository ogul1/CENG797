import inet.common.INETDefs;
import inet.common.packet.chunk.Chunk;

namespace mstclustering;

enum MstClusteringMsgType {
    MSG_HELLO = 0;
    MSG_TOPOLOGY_UPDATE = 1;
    MSG_CLUSTER_JOIN = 2;
    MSG_CLUSTER_HEAD = 3;
    MSG_CLUSTER_ACK = 4;
    MSG_CLUSTER_LEAVE = 5;
    MSG_EDGE_INFO = 6;
};

enum NodeRole {
    ROLE_UNDECIDED = 0;
    ROLE_CLUSTER_MEMBER = 1;
    ROLE_CLUSTER_HEAD = 2;
    ROLE_GATEWAY = 3;
};

class HelloPacket extends inet::FieldsChunk {
    int nodeId;
    double posX;
    double posY;
    double posZ;
    double energy;
    int clusterId = -1;
    int clusterHeadId = -1;
    int nodeRole;
    int sequenceNumber;
    int numNeighbors;
    simtime_t timestamp;
}

class TopologyUpdatePacket extends inet::FieldsChunk {
    int sourceId;
    int destId;
    double weight;
    bool isActive;
    int sequenceNumber;
}

class ClusterJoinPacket extends inet::FieldsChunk {
    int nodeId;
    int clusterId;
    int clusterHeadId;
    double energy;
    int sequenceNumber;
}

class ClusterHeadPacket extends inet::FieldsChunk {
    int clusterId;
    int clusterHeadId;
    int memberCount;
    double avgEnergy;
    int sequenceNumber;
}

class EdgeInfoPacket extends inet::FieldsChunk {
    int sourceId;
    int destId;
    double weight;
    int mstId;
    int sequenceNumber;
}
