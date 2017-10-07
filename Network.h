#include <vector>

using namespace std;

class Network {
	public:
    // *** Variables ***
	unsigned int NumofNodes;
	vector< vector<double> > NodesWeight;
	vector< vector< vector<int> > > routingTable;	



	// *** Functions ***	
		void read_topology ();
		void init ();

	private:
		Dijkstra dijkstra;
};
