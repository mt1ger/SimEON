#include <vector>
#include "Network.h"

using namespace std;

class Topology {
	public:
    // *** Variables ***
	Topology (Network * net) {network = net;}
	~Topology () {}
	// unsigned int NumofNodes;
	// vector< vector<double> > NodesWeight;



	// *** Functions ***	
		void read_topology ();

	private:
		Network * network;
};
