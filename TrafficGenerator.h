#include "RandomVariable.h"
#include "EventQueue.h"
#include "Network.h"
// #include "CircuitRequest.h"
// #include "CircuitRelease.h"


class TrafficGenerator {
	public:
		TrafficGenerator (Network * net, EventQueue * eq) {network = net; eventQUeue = eq;}
		~TrafficGenerator () {}

		void gen_unicast_sd (unsigned int * src, unsigned int * dest);
		void gen_temporal_parameters (double * time, unsigned int LorM); 
		void gen_request (double startTime);

	private:
		Network * network;
		EventQueue * eventQUeue;
};
