#include <iostream>
#include <vector>

using namespace std;

class Event {
	public:
	Event () {}
	~Event () {}

	// unsigned int EventID;
	double EventTime;
	unsigned int EventType;

	private:
};


class CircuitRequest : public Event {
	public:
		CircuitRequest (unsigned int src, unsigned int dest, double startTime, double duration, unsigned int OccupiedSpectralSlots); 
		~CircuitRequest () {}
		unsigned int Src;
		unsigned int Dest;
		double StartTime;
		double Duration;
		unsigned int OccupiedSpectralSlots;	
};


class CircuitRelease : public Event {
	public:
		CircuitRelease (vector<int> & circuitRoute, vector<int> & occupiedSpectralSection, double releaseTime);
		~CircuitRelease () {}
		// unsigned int CircuitID;
		vector<int> CircuitRoute;
		vector<int> OccupiedSpectralSection;
		double ReleaseTime;
	
};
