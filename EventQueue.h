#include <vector>
#include "Event.h" 
#include <list> 

class EventQueue {
	public:
		list<Event *> ev_Queue;

		void queue_insert (Event * event);
};
