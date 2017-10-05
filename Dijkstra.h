#include "Network.h" 

class DijkstraSP {
	public:
		void shortest_path (int src, int dest, vector<int> &predecessors);
		void ajacent_nodes (vector< vector<int> > &AjacentNodes);

	private:
		Network network;
		vector< vector<int> > AjacentNodes;
};
