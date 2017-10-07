#include <iostream>
#include <vector>
#include "Dijkstra.h"

using namespace std;


int main (void) {
	Network network;
	Dijkstra dijkstra;
	vector<int> predecessors;
		
	
	dijkstra.shortest_path (0, -1, predecessors);
	
	cout << "\n";
	for (int i = 0; i < predecessors.size (); i++) {
		cout << ' ' << predecessors[i] + 1;	
	}
	cout << endl;

	return 1;
}
