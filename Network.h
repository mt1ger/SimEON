#ifndef _NETWORK_H
#define _NETWORK_H

#include <vector>
// #include "TrafficGenerator.h"
// #include "RoutingTable.h"
#include "EventQueue.h"


#define NumofSpectralSlots 300


using namespace std;

class RoutingTable;

class Network {
	public:
		/*** Functions ***/  
		void init ();
		void simulation ();


		/*** VARIABLES ***/ 
		// Inputted Variables   
		char FileName[500];
		unsigned int Lambda, Mu;
		long long NumofRequests;

		// Topology Variables
		unsigned int NumofNodes; 
		vector< vector<double> > NodesWeight;
		vector< vector< vector<int> > > routingTable;

		// Timer and counters 
		long long RequestCounter;
		long long NumofAllocatedRequests;
		long long NumofDoneRequests;
		long long NumofFailedRequests;
		double SystemClock;

		vector< vector< vector<bool> > > SpectralSlots;

		
	private:
};

#endif
