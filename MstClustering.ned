package mstclustering;

import inet.applications.contract.IApp;

simple MstClustering like IApp
{
    parameters:
        @display("i=block/network2");
        @class(MstClustering);

        string interfaceTableModule = default("^.interfaceTable");

        double helloInterval @unit(s) = default(1s);
        double clusterTimeout @unit(s) = default(5s);

        double mstUpdateInterval @unit(s) = default(2s);
        bool enableDynamicMst = default(true);

        int maxClusters = default(0);
        int maxClusterSize = default(10);
        double clusterThreshold = default(0.5);

        double edgeWeightAlpha = default(0.5);
        double edgeWeightBeta = default(0.3);
        double edgeWeightGamma = default(0.2);

        double communicationRange @unit(m) = default(250m);
        int localPort = default(9999);
        int destPort = default(9999);

        @signal[clusterId](type=long);
        @signal[clusterSize](type=long);
        @signal[isClusterHead](type=long);
        @signal[reClusteringCount](type=long);
        @signal[controlOverhead](type=long);
        @signal[clusterStability](type=double);
        @signal[numNeighbors](type=long);
        @signal[energy](type=double);
        @signal[numClusters](type=long);
        @signal[mstEdgeCount](type=long);

        @statistic[clusterId](title="Cluster ID"; record=vector,histogram);
        @statistic[clusterSize](title="Cluster Size"; record=vector,mean,histogram);
        @statistic[isClusterHead](title="Is Cluster Head"; record=vector,mean);
        @statistic[reClusteringCount](title="Re-clustering Count"; record=last,vector);
        @statistic[controlOverhead](title="Control Overhead"; record=count,vector);
        @statistic[clusterStability](title="Cluster Stability Time"; record=vector,mean,max);
        @statistic[numNeighbors](title="Number of Neighbors"; record=vector,mean,histogram);
        @statistic[energy](title="Remaining Energy"; record=vector,mean,min);
        @statistic[numClusters](title="Number of Clusters"; record=vector,mean);
        @statistic[mstEdgeCount](title="MST Edge Count"; record=vector,mean);

    gates:
        input socketIn;
        output socketOut;
}

