#include <iostream>
#include <cstdio>
#include <vector>
#include "Network.h"

using namespace std;

void Network::ReadTopology (void) {
	FILE * nettopo;
	char file_name[100];
	unsigned int number;
	unsigned int NumofNodes = 0;
	int temp;
	vector <int> HNodesWeight;
	vector< vector<int> > NodesWeight;

	cout << "Choose from the available network topology:" << endl;
	cout << "1. NSF" << endl;
	cout << "2. ESNET" << endl;
	cout << "3. ITALY" << endl;	
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

	fscanf (nettopo, "%d", &NumofNodes);		
	cout << "There are " << NumofNodes << " nodes in this topology." << endl;

	for (int i = 0; i < NumofNodes; i++) {
		for (int j = 0; j < NumofNodes; j++) {
			// fscanf (nettopo, "%d", &nodes[i][j]);
			fscanf (nettopo, "%d", &temp); 
			HNodesWeight.push_back (temp);
		}
		NodesWeight.push_back (HNodesWeight);
		HNodesWeight.clear ();
	}

	printf ("\n");
	for (int i = 0; i < NumofNodes; i++) {
		for (int j = 0; j < NumofNodes; j++) {
			printf ("%d ", NodesWeight[i][j]);
		}
		printf ("\n");
	}
	
}
