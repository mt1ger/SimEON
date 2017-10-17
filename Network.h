#ifndef _NETWORK_H
#define  _NETWORK_H

#include <vector>
#define  NumofSpectralSlots 300
// #include "TrafficGenerator.h"
// #include "RoutingTable.h"
//
using namespace std;


class Network {
	public:
		/*** Functions ***/  
		void init ();
		void simulation ();


		/*** VARIABLES ***/ 
		// Inputted Variables   
		unsigned int Lambda, Mu;
		long long NumofRequests;

		// Topology Variables
		unsigned int NumofNodes; 
		vector< vector<double> > NodesWeight;
		vector< vector< vector<int> > > routingTable;

		// Intermediate Variables
		long long QueuedRequests;
		long long NumofDoneRequests;

		vector< vector< vector<bool> > > SpectralSlots;

		
	private:
};

#endif
