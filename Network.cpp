#include <iostream> 
#include "RoutingTable.h"
// #include "Topology.h"

using namespace std;

void Network::init () {
	RoutingTable routinGTable (this);	
	routinGTable.generate_routing_table ();
}

