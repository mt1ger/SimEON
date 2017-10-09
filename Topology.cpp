#include <iostream>
#include <cstdio>
#include <vector>
#include "Topology.h"

using namespace std;

void Topology::read_topology (void) {
	FILE * nettopo;
	char file_name[100];
	unsigned int number;
	int temp;
	vector <double> HNodesWeight;

	cout << "**************************************************" << endl;
	cout << "Choose from these available network topologies:" << endl; 
	cout << "1. NSF" << endl;
	cout << "2. ESNET" << endl;
	cout << "3. ITALY" << endl;	
	cout << "**************************************************" << endl;

	cin >> number;
	switch (number) {
		case 1: 
			cout << "The topology chosen is NSF." << endl;
			nettopo = fopen ("./Topology/NFS14.txt", "r");
			break;
		case 2: 
			cout << "The topology chosen is ESNET." << endl;
			nettopo = fopen ("./Topology/ESNET14.txt", "r");
			break;
		case 3: 
			cout << "The topology chosen is ITALY." << endl;
			nettopo = fopen ("./Topology/ITALY21.txt", "r");
			break;
	}

	cout << "what" << network->NumofNodes << endl;

	fscanf (nettopo, "%d", &network->NumofNodes);		
	cout << "There are " << network->NumofNodes << " nodes in this topology." << endl;

	for (int i = 0; i < network->NumofNodes; i++) {
		for (int j = 0; j < network->NumofNodes; j++) {
			// fscanf (nettopo, "%d", &nodes[i][j]);
			fscanf (nettopo, "%d", &temp); 
			HNodesWeight.push_back (temp);
		}

	network->NodesWeight.push_back (HNodesWeight);
		HNodesWeight.clear ();
	}

	fclose (nettopo);
}


