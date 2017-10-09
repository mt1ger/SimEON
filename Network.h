#include <vector>
// #include "TrafficGenerator.h"
// #include "RoutingTable.h"
//
using namespace std;

class Network {
	public:
		void init ();

		unsigned int NumofNodes; 
		vector< vector<double> > NodesWeight;
		vector< vector< vector<int> > > routingTable;
		


		void print ();
	private:
};
