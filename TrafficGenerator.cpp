#define DEBUG_print_new_built_Event

#include "TrafficGenerator.h"
#include <string>
#include <fstream>
#include <cmath>


using namespace std;


void TrafficGenerator::gen_unicast_sd (unsigned int * src, unsigned int * dest) {
	do {
		* src = uniform_rv (network->NumofNodes);
	} while (* src == network->NumofNodes);


	do {
		* dest = uniform_rv (network->NumofNodes);
	} while ((* dest == * src) || (* dest == network->NumofNodes));
	
}


void TrafficGenerator::gen_temporal_parameters (double * time, double LorM) {
	* time = exponential_rv (LorM);
}


void TrafficGenerator::gen_first_request () {
	unsigned int src, dest, occupiedSpectralSlots;
	double startTime = 0;
	double duration;
	CircuitRequest * request;

	gen_unicast_sd (&src, &dest);
	gen_temporal_parameters (&duration, network->Mu);
	do {
		occupiedSpectralSlots = uniform_rv (MAX_OCCUPIED_SPECTRAL_SLOTS);
	} while (occupiedSpectralSlots == 0);

	#ifdef MODIFY_integer
	duration = ceil( duration);
	startTime = (int) startTime;
	#endif
	
	request = new CircuitRequest (src, dest, startTime, duration, occupiedSpectralSlots, network->RequestCounter);
	
	network->RequestCounter++;

	#ifdef DEBUG_print_new_built_Event
	cout << "\tNew Built event:" << endl;
	cout << '\t' << request->Src << ' ' << request->Dest << ' ' << request->StartTime << ' ' << request->Duration << ' ' << request->OccupiedSpectralSlots << endl;
	int datasize = request->OccupiedSpectralSlots * 12.5;
	string requestPara;
	requestPara = to_string (request->Src + 1) + ',' + to_string (request->Dest + 1) + ',' + to_string (request->StartTime) + ',' + to_string (request->Duration) + ',' + to_string (datasize) + '\n'; 
	ofstream fp;
	fp.open ("RP.csv", fstream::app);
	fp << requestPara;
	fp.close ();
	#endif

	eventQUeue->ev_Queue.push_back (request);
}


//releases' generation will be taken care of in "handle_requests" in "ResourceAssignment.cpp" 
void TrafficGenerator::gen_request (double systemTime) {
	unsigned int src, dest, occupiedSpectralSlots;
	double time, startTime, duration;
	CircuitRequest * request;

	gen_unicast_sd (&src, &dest);
	gen_temporal_parameters (&duration, network->Mu);
	gen_temporal_parameters (&time, network->Lambda);
	do {
		occupiedSpectralSlots = uniform_rv (MAX_OCCUPIED_SPECTRAL_SLOTS);
	} while (occupiedSpectralSlots == 0);
	startTime = systemTime + time;

	#ifdef MODIFY_integer
	duration = ceil( duration);
	startTime = ceil( startTime);
	#endif
	
	request = new CircuitRequest (src, dest, startTime, duration, occupiedSpectralSlots, network->RequestCounter);
	
	network->RequestCounter++;

	#ifdef DEBUG_print_new_built_Event
	cout << "\tNew Built event:" << endl;
	cout << '\t' << request->EventID << ' ' <<request->Src << ' ' << request->Dest << ' ' << request->StartTime << ' ' << request->Duration << ' ' << request->OccupiedSpectralSlots << endl;
	int datasize = request->OccupiedSpectralSlots * 12.5;
	string requestPara;
	requestPara = to_string (request->Src + 1) + ',' + to_string (request->Dest + 1) + ',' + to_string (request->StartTime) + ',' + to_string (request->Duration) + ',' + to_string (datasize) + '\n'; 
	ofstream fp;
	fp.open ("RP.csv", fstream::app);
	fp << requestPara;
	fp.close ();
	#endif

	eventQUeue->queue_insert (request);
}
