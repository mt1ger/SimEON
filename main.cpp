#include <iostream>
#include <vector>
#include "RoutingTable.h"

using namespace std;


int main (void) {
	Network * network;
	Network net;
	network = &net;
	RoutingTable routinGTable (network);

	network->init ();
	routinGTable.get_shortest_path (1, 10);
	cout << "where is the rest" << endl;
	for (int i = 0; i < 14; i++) {

		for (int j = 0; j < 14; j++) {
			routinGTable.get_shortest_path (i, j);
		}}

	return 1;
}
