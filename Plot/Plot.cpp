#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <thread>
#include <mutex>

#define NUMOFSEEDS 40
#define NUMOFTHREADS 40 

using namespace std;
mutex mtx;

void thread_function (string cmd) {
	mtx.lock ();
	system (cmd.c_str ());
	// cout << cmd << endl;
	mtx.unlock ();
}

int main () {
	vector<int> Core;
	double Number;
	static unsigned int NumofRequests = 10000;
	static string Exec = "~/Desktop/SimEON/Simulator"; 
	static string Topo = "~/Desktop/Simulator/SimSDM-EON/Topology/NSF14.txt";
	thread ThreadPointer[NUMOFTHREADS];
	unsigned int cnt = 0;

	ofstream plot ("Plot.txt");

	cout << "Input a number for seed and press enter: " << endl;
	cin >> Number; 
	srand (Number);


		for (unsigned int seed = 0; seed < NUMOFSEEDS; seed++) {
			// for (unsigned int lambda = 100; lambda < 491; lambda = lambda + 10) {
				string Cmd = Exec + ' ' + Topo + ' ' + to_string (NumofRequests) + ' ' + '4' + " 0.05 " + to_string ((double) rand () / 65535);
				ThreadPointer[cnt] = thread (thread_function, Cmd);
				cnt ++;
			// }
		} 
	

	for (int i = 0; i < NUMOFTHREADS; i++) {
		ThreadPointer[i].join ();
	}

	plot.close ();

	return 1;
}





