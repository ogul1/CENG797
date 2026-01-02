package mstclustering;

import inet.node.inet.AdhocHost;

module MstClusteringNode extends AdhocHost
{
    parameters:
        @display("i=device/cellphone");
        
        forwarding = default(true);
        
        numApps = default(0);
        
    submodules:
        mstClustering: MstClustering {
            @display("p=700,76;is=s");
        }
        
    connections:
        mstClustering.socketOut --> at.in++;
        mstClustering.socketIn <-- at.out++;
}

module MstClusteringNodeAodv extends MstClusteringNode
{
    parameters:
        @display("i=device/cellphone");
    submodules:
        aodv: inet.routing.aodv.Aodv {
            @display("p=825,226");
        }
    connections:
        aodv.socketOut --> at.in++;
        aodv.socketIn <-- at.out++;
}

module MstClusteringNodeDsdv extends MstClusteringNode
{
    parameters:
        @display("i=device/cellphone");
    submodules:
        dsdv: inet.routing.dsdv.Dsdv {
            @display("p=825,226");
        }
    connections:
        dsdv.socketOut --> at.in++;
        dsdv.socketIn <-- at.out++;
}

module MstClusteringNodeGpsr extends MstClusteringNode
{
    parameters:
        @display("i=device/cellphone");
    submodules:
        gpsr: inet.routing.gpsr.Gpsr {
            @display("p=825,226");
        }
    connections:
        gpsr.socketOut --> at.in++;
        gpsr.socketIn <-- at.out++;
}
