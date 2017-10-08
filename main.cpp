#include <iostream>
#include <vector>
#include "Network.h"

using namespace std;


int main (void) {
	Network network;

	network.init ();
	network.routinGTable.get_shortest_path (1, 10);

	
cout << endl;
for (int i = 0; i < network.Rtable[2].size (); i++) {
	for (int k = 0; k < network.Rtable[2][i].size (); i++) {
		cout << network.Rtable[2][i][k] << ' ' << endl;	
	}
}
	cout << "\n";
	for (int i = 0; i < network.Rtable.size (); i++) {
		cout << endl;
		for (int j = 0; i < network.Rtable[i].size (); j++) {
			for (int k = 0; k < network.Rtable[i][j].size (); k++) {
				cout << network.Rtable[i][j][k] + 1 << ' '; 	
			}
			cout << endl;
		}
	}
	cout << endl;

	return 1;
}
