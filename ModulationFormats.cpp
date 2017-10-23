#include <iostream>
#include <string>
#include "ModulationFormats.h"

using namespace std;

/****************************************
 * Modulation Format VS Reachability:
 * BPSK:       9600km   1bit/symbol
 * QPSK:       4800km   2bits/symbol
 * 8QAM:       2400km   3bits/symbol
 * 16QAM:      1200km   4bits/symbol
 * DP_QPSK:    3000km   4bits/symbol
 * DP_8QAM:    1000km  	6bits/symbol 
 * DP_16QAM:    650km   8bits/symbol
 ****************************************/


void ModulationFormats::spectalslots_computation (unsigned int BitsPerSymbol) {
	// "bm" means before modulation
	if (bm_SptialSlots % BitsPerSymbol != 0) {
		SpectralSlots = bm_SpectralSlots / BitsPerSymbol + 1;	
	}
	else SpectralSlots = bm_SptialSlots / BitsPerSymbol;
}


string ModulationFormats::mf_chosen () {
	int MaxDist = 0; 
	string MF;
	for (int i = 0; i < shortestPath.size (); i++) {
		if (MaxDist <= (int) shortestPath[i]) {
			MaxDist = (int) shortestPath[i];	
		}
	}

	if (MaxDist > 4800 && MaxDist <= 9600) {
		m_Format = BPSK;
		spectalslots_computation (1);
	}
	else if (MaxDist > 3000 && MaxDist <= 4800) {
		m_Format = QPSK;
		spectalslots_computation (2);
	}
	else if (MaxDist > 1000 && MaxDist <= 3000) {
		m_Format = DP_QPSK;
		spectalslots_computation (4);
	}
	// else if (MaxDist > 1200 && MaxDist <= 2400) {
	// 	MF = "8QAM";
	// 	spectalslots_computation (3);
	// }
	// else if (MaxDist > 1000 && MaxDist <= 1200) {
	// 	MF = "16QAM";
	// 	spectalslots_computation (4);
	// }
	else if (MaxDist > 650 && MaxDist <= 1000) {
		m_Format = DP_8QAM;
		spectalslots_computation (6);
	}
	else if (MaxDist <= 650) {
		m_Format = DP_16QAM;
		spectalslots_computation (8);
	}
	
}
