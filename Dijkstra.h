#include <vector>
#include "Topology.h" 

using namespace std;

class Dijkstra {
	public:
		void shortest_path (int src, int dest, vector<int> &predecessors);
		void ajacent_nodes (vector< vector<int> > &AjacentNodes);

		vector< vector<int> > AjacentNodes;
		Topology topology;
	private:
};
