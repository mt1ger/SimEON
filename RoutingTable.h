#include "Dijkstra.h"
// #include "Network.h"
using namespace std;

class RoutingTable {
	public:
		RoutingTable (Network * net) {network = net;}
		~RoutingTable () {};

		vector<int> get_shortest_path (int src, int dest);
		// vector< vector< vector<int> > > routingTable;

		unsigned int NumofNodes;

	void generate_routing_table ();
	private:
		vector< vector<int> > predecessors;
		vector<vector<int> > single_src_routing_table (int src);
		void get_predecessor_list ();
		
		// Dijkstra dijkstra;
		Network * network;
};
