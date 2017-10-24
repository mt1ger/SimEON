// #define DEBUG_test_sequence_in_queue

#include <iostream> 
#include "RoutingTable.h"
#include "Network.h"
#include "TrafficGenerator.h"
#include "Event.h"
#include "ResourceAssignment.h"



using namespace std;

void Network::init () {
	vector<bool> x_SpectralSlots;
	vector< vector<bool> > xy_SpectralSlots;

	RoutingTable routinGTable (this);   
	routinGTable.generate_routing_table ();

	for (int i = 0; i < NumofNodes; i++) {
		for (int j = 0; j < NumofNodes; j++) {
			for (int k = 0; k < NumofSpectralSlots; k++) {
				x_SpectralSlots.push_back (false);
			}
			xy_SpectralSlots.push_back (x_SpectralSlots);
			x_SpectralSlots.clear ();
		}
		SpectralSlots.push_back (xy_SpectralSlots);
		xy_SpectralSlots.clear ();
	}

	SystemClock = 0;
	RequestCounter = 0;
	NumofDoneRequests = 0;
	NumofFailedRequests = 0;
	NumofAllocatedRequests = 0;
}

// #ifdef DEBUG_enable_traffic_allocation_components
void Network::simulation () {
	EventQueue *eventQueue = new EventQueue ();
	TrafficGenerator trafficGenerator (this, eventQueue);
	ResourceAssignment resourceAssignment (this, eventQueue);


	// Generate the first event
	trafficGenerator.gen_first_request ();

	while (!eventQueue->ev_Queue.empty ()) {
		Event * event;
		event = eventQueue->ev_Queue.front ();

		// cout << "\tThe event time is " << event->EventTime << endl;
		// cout << "\tThe system time is " << SystemClock << endl;

		if (SystemClock <= event->EventTime) {
			SystemClock = event->EventTime;
		}
		// cout << "\tThe system time is " << SystemClock << endl;


		#ifdef DEBUG_test_sequence_in_queue
		// The code to test if Events in Queue is in right order
		list<Event*>::iterator iter;
		cout << "Print Event key properties in Queue" << endl;
		for (iter = eventQueue->ev_Queue.begin (); iter != eventQueue->ev_Queue.end (); iter++) {
			cout << (*iter)->EventID << ' ' ;
			if ((*iter)->EventType == c_Release) cout << "Release" << ' ';
			else if ((*iter)->EventType == c_Request) cout << "Request" << ' ';
			cout << (*iter)->EventTime << '\t';
		}
		cout << endl;
		#endif


		if (event->EventType == c_Request) {
			resourceAssignment.handle_requests ((CircuitRequest *) event);
			trafficGenerator.gen_request (SystemClock);


		}
		else if (event->EventType == c_Release) {
			resourceAssignment.handle_releases ((CircuitRelease *) event);
		}

		eventQueue->ev_Queue.pop_front (); //This will destroy the poped Event *.

cout << " " << NumofDoneRequests << " and " << NumofRequests << endl;
		if (RequestCounter == NumofRequests) break;
	}

	cout << endl << "************************************************************" << endl;
	cout << "Network Load: " << Lambda / Mu << " Erlang" << endl; 
	cout << "Blocking Probability: " << (double) NumofFailedRequests / (double) NumofRequests << endl;
}

