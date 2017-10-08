#include <iostream>
#include <vector>
#include <cmath>
#include "Dijkstra.h"

#define EPSILON 0.00000001

using namespace std;

// Comparing numbers with double involved is trying to tell if the numbers are close enough. 
int compare_double (double a, double b) {
	return abs (a - b) < EPSILON;
}


void Dijkstra::ajacent_nodes (vector< vector<int> > &AjacentNodes) {

	vector <int> HAjecentNodes;

	for (int i = 0; i < topology.NumofNodes; i++) {
		for (int j = 0; j <topology.NumofNodes; j++) {
			if (!compare_double (topology.NodesWeight[i][j], -1) && (j != i))
				HAjecentNodes.push_back (j); 	
		}
		AjacentNodes.push_back (HAjecentNodes);
		HAjecentNodes.clear ();
	}
}


void Dijkstra::shortest_path (int src, int dest, vector<int> &predecessors) {

	vector<double> dist;	
	vector<bool> visited;
	// vector < vector<int> > AjacentNodes;
	int k;
	int next;
	int MinDist;

	// topology.read_topology ();
	// ajacent_nodes (AjacentNodes);

	// To initialize the Algorithm:
	vector<int> HPredecessor (1, -1);
	for (int i = 0; i < topology.NumofNodes; i++) {
		dist.push_back (INFINITY);
		visited.push_back (false);
		predecessors.push_back (-1);
	}




	int counter = 0;
	dist[src] = 0;
	visited[src] = true;
	next = src;

	while (counter < topology.NumofNodes) {

		for (int j = 0; j < AjacentNodes[next].size (); j++) {
			if (!visited[AjacentNodes[next][j]] && ((dist[next] + topology.NodesWeight[next][AjacentNodes[next][j]]) < dist[AjacentNodes[next][j]])) { 
				dist[AjacentNodes[next][j]] = (dist[next] + topology.NodesWeight[next][AjacentNodes[next][j]]);	
				predecessors.at (AjacentNodes[next][j]) = next;

			}		
		}

		MinDist = INFINITY;
		for (k = 0; k < topology.NumofNodes; k++) {
			if ((MinDist > dist[k]) && !visited[k]) {
				MinDist = dist[k];
				next = k;
			}
		}
		visited[next] = true;

		if (next == dest) {
			break;
		}
		counter++;
	}
}




