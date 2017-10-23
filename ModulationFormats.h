#ifndef _MODULATIONFORMAT_H
#define _MODULATIONFORMAT_H

#include "Event.h"

enum MF_t {BPSK, QPSK, DP_QPSK, DP_8QAM, DP_16QAM};

class ModulationFormats {
	public:
		string mf_chosen ();

		MF_t m_Format;
	private:
		CircuitRequest * request; 
};

#endif
