#include <iostream> 
#include "RoutingTable.h"
// #include "TrafficGenerator.h"

using namespace std;

void Network::init () {
	vector<bool> x_SpectralSlots;
	vector< vector<bool> > xy_SpectralSlots;

	RoutingTable routinGTable (this);	
	routinGTable.generate_routing_table ();


	for (int i = 0; i < NumofNodes; i++) {
		for (int j = 0; j < NumofNodes; j++) {
			for (int k = 0; k < NumofSpectralSlots; k++) {
				x_SpectralSlots.push_back (false);
			}	
			xy_SpectralSlots.push_back (x_SpectralSlots);
			x_SpectralSlots.clear ();
		}
		SpectralSlots.push_back (xy_SpectralSlots);
		xy_SpectralSlots.clear ();
	}
}


void Network::simulation () {
	// TrafficGenerator trafficGenerator (this);
	
}

