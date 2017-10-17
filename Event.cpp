#include "Event.h"

CircuitRequest::CircuitRequest (unsigned int src, unsigned int dest, double startTime, double duration, unsigned int occupiedSpectralSlots) {
	Src = src;
	Dest = dest;
	StartTime = startTime;
	Duration = duration;
	EventTime = startTime;
	EventType = 1;	
	OccupiedSpectralSlots = occupiedSpectralSlots;
}


CircuitRelease::CircuitRelease (vector<int> &circuitRoute, vector<int> &occupiedSpectralSection, double releaseTime) {
	CircuitRoute = circuitRoute;
	OccupiedSpectralSection = occupiedSpectralSection;
	ReleaseTime = releaseTime;
	EventTime = releaseTime;
}
