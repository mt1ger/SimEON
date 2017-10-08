#include <vector>

using namespace std;

class Topology {
	public:
    // *** Variables ***
	unsigned int NumofNodes;
	vector< vector<double> > NodesWeight;



	// *** Functions ***	
		void read_topology ();

	private:
};
