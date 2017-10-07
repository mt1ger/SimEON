#include "Network.h" 

class Dijkstra {
	public:
		void shortest_path (int src, int dest, vector<int> &predecessors);
		void ajacent_nodes (vector< vector<int> > &AjacentNodes, unsigned int NumofNodes);

		vector< vector<int> > AjacentNodes;
		Network network;
	private:
};
