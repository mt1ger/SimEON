#include <iostream>
#include <vector>
#include "DijsktraSP.h"

using namespace std;

void DijkstraSP::ShortestPath (int src, int dest, vector<vector<int>> graph) {
	vector<int> dist;	


	// To initialize the Algorithm: 
	for (int i = 0; i < NumofNodes; i++) {
		for (int j = 0; j < Dist; j++) {
			preceedors[i][j] = 0;	
		}
	}
}
