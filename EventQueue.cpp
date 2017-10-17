#include "EventQueue.h" 

using namespace std;

void EventQueue::queue_insert (Event * event) {

	list<Event *>::iterator i;

	for (i = ev_Queue.end (); i != ev_Queue.begin (); i--) { 
		if (event->EventTime > (*i)->EventTime) {
			i++;
			ev_Queue.insert (i, event);	
			break;
		}
	}
}
