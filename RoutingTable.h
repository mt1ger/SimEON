#include "Dijkstra.h"

class RoutingTable {
	public:
		vector<int> get_shortest_path (int src, int dest);
		vector< vector< vector<int> > > routingTable;

		unsigned int NumofNodes;

	void generate_routing_table ();
	private:
		vector< vector<int> > predecessors;
		vector<vector<int> > single_src_routing_table (int src);
		void get_predecessor_list ();
		
		Dijkstra dijkstra;
};
