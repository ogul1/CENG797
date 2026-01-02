package mstclustering;

import inet.networklayer.configurator.ipv4.Ipv4NetworkConfigurator;
import inet.physicallayer.wireless.common.contract.packetlevel.IRadioMedium;
import inet.visualizer.contract.IIntegratedVisualizer;
import inet.environment.common.PhysicalEnvironment;
import inet.node.contract.INetworkNode;

network MstClusteringNetwork
{
    parameters:
        int numNodes = default(20);
        
        double playgroundSizeX @unit(m) = default(1000m);
        double playgroundSizeY @unit(m) = default(1000m);
        double playgroundSizeZ @unit(m) = default(0m);
        
        bool hasVisualizer = default(true);
        bool hasPhysicalEnvironment = default(false);
        
        @display("bgb=600,600;bgg=100,1,grey95");
        
        @figure[title](type=label; pos=0,-1; anchor=sw; color=darkblue);
        
        @figure[numClustersText](type=text; pos=20,20; anchor=w; font=,14; color=blue;
            text="Active Clusters: 0");
        
        @figure[avgClusterSizeText](type=text; pos=20,40; anchor=w; font=,14; color=blue;
            text="Avg Cluster Size: 0.0");
        
    submodules:
        visualizer: <default(firstAvailableOrEmpty("IntegratedCanvasVisualizer"))> like IIntegratedVisualizer if hasVisualizer && typename != "" {
            @display("p=50,50;is=s");
        }
        
        configurator: Ipv4NetworkConfigurator {
            @display("p=50,100;is=s");
        }
        
        radioMedium: <default("UnitDiskRadioMedium")> like IRadioMedium {
            @display("p=50,150;is=s");
        }
        
        physicalEnvironment: PhysicalEnvironment if hasPhysicalEnvironment {
            @display("p=50,200;is=s");
        }
        
        node[numNodes]: <default("MstClusteringNode")> like INetworkNode {
            @display("r=,,#707070;p=200,200");
        }
}

network MstClusteringNetworkSmall extends MstClusteringNetwork
{
    parameters:
        numNodes = default(10);
        playgroundSizeX = default(500m);
        playgroundSizeY = default(500m);
}

network MstClusteringNetworkMedium extends MstClusteringNetwork
{
    parameters:
        numNodes = default(30);
        playgroundSizeX = default(800m);
        playgroundSizeY = default(800m);
}

network MstClusteringNetworkLarge extends MstClusteringNetwork
{
    parameters:
        numNodes = default(100);
        playgroundSizeX = default(2000m);
        playgroundSizeY = default(2000m);
}

network MstClusteringNetworkWithObstacles extends MstClusteringNetwork
{
    parameters:
        hasPhysicalEnvironment = true;
        numNodes = default(25);
        playgroundSizeX = default(800m);
        playgroundSizeY = default(800m);
}
