#include "TrafficGenerator.h"

using namespace std;

void TrafficGenerator::gen_unicast_sd (unsigned int * src, unsigned int * dest) {
	* src = uniform_rv (network->NumofNodes);
	do {
		* dest = uniform_rv (network->NumofNodes);
	} while (* dest == * src);
}


void TrafficGenerator::gen_temporal_parameters (double * time, unsigned int LorM) {
	* time = exponential_rv (LorM);
}


//releases' generation will be taken care of in "handle_requests" in "ResourceAssignment.cpp" 
void TrafficGenerator::gen_request (double startTime) {
	unsigned int src, dest, occupiedSpectralSlots;
	double duration;
	CircuitRequest * request;

	gen_unicast_sd (&src, &dest);
	gen_temporal_parameters (&duration, network->Mu);
	occupiedSpectralSlots = uniform_rv (300);
	
	request = new CircuitRequest (src, dest, startTime, duration, occupiedSpectralSlots);
	
	eventQUeue->queue_insert (request);
	network->QueuedRequests++;
}
