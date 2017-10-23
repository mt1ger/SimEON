#include "Event.h"

class CircuitRequest : public Event {
	unsigned int Src;
	unsigned int Dest;
	double StartTime;
	double Duration;
	unsigned int SpectralSlots;	
};
