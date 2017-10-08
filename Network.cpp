#include <iostream>
#include "Network.h"

void Network::init () {
	
	routinGTable.generate_routing_table ();
	Rtable = routinGTable.routingTable;
	
}
