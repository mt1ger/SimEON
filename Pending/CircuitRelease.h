#include "Event.h"

class CircuitRelease : public Event {
	unsigned int CircuitID;
	vector<int> CircuitRoute;
	vector<int> OccupiedSpectralSlots;
	double ReleaseTime;
	
};
