#include "EventQueue.h"
#include "RoutingTable.h"

class ResourceAssignment {
	public:
		ResourceAssignment (Network * net) {network = net;}
		~ResourceAssignment () {}

		vector< vector<int> > SourceAvailableSections;

		void handle_requests (CircuitRequest * circuitRequest);
		void handle_releases ();
		void check_availability_source (unsigned int predecessor, unsigned int successor);
		void check_availability_link (unsigned int predecessor, unsigned int successor, int i, bool * AvailableFlag); 

	private:
		Network * network;
};
