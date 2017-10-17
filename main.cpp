#define AAA

#include <iostream>
#include <vector>
#include "Network.h"
#include "RoutingTable.h"

using namespace std;


int main (void) {
	Network * network;
	Network net;
	network = &net;
	RoutingTable routinGTable (network);

	network->init ();

#ifdef AAA
	cout << "where is the rest" << endl;
	for (int i = 0; i < 14; i++) {
		cout << "Table for " << i << endl;
		for (int j = 0; j < 14; j++) {
			for (int k = 0; k < NumofSpectralSlots; k++) {
				cout << network->SpectralSlots[i][j][k];		
			}
			cout << " End of one link " << j << endl;
		}
	}
#endif

	return 1;
}
