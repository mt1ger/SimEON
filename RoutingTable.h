#include "Dijkstra.h"

class RoutingTable {
	public:
		vector<int> get_shortest_path (int src, int dest);

	private:
		vector< vector<int> > predecessors;
		vector<vector<int> > single_src_routing_table (int src);
		void get_predecessor_list ();
		void generate_routing_table ();
		
		vector< vector< vector<int> > > routingTable;
		Dijkstra dijkstra;
};
