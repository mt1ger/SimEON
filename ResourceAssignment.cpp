/**************************************************
 * First-Fit 
 **************************************************/

#include <iostream>
#include "ResourceAssignment.h"
 

//Used event to represent Event instance
void ResourceAssignment::check_availability_source (unsigned int predecessor, unsigned int successor) {
	bool AvailableFlag = true;
	vector<int> HSourceAvailableSections;

	for (int i = 0; i < NumofSpectralSlots; i++) {
		AvailableFlag = true;
		if (network->SpectralSlots[predecessor][successor][i] == false) {
			for (int j = 0; j < event->OccupiedSpectralSlots; j++) {
				if (network->SpectralSlots[predecessor][successor][i + j] == true) {
					AvailableFlag = false;
					break;	
				}
			}

			if (AvailableFlag == true) {
				HSourceAvailableSections.push_back (i);	
				HSourceAvailableSections.push_back (i + NumofSpectralSlots - 1);
			}
			SourceAvailableSections.push_back (HSourceAvailableSections);
			HSourceAvailableSections.clear ();	
		}
	}
}

//Used event to represent Event instance
void ResourceAssignment::check_availability_link (unsigned int predecessor, unsigned int successor, int i, bool * AvailableFlag) {

	for (int j = SourceAvailableSections[i][0]; j < SourceAvailableSections[i][1]; j++) {
		if (network->SpectralSlots[predecessor][successor][j] == true) {
			* AvailableFlag = false;
			break;	
		}	
	}
}



void ResourceAssignment::handle_requests (CircuitRequest * circuitRequest) {
	RoutingTable routingTable (network);	

	vector<int> CircuitRoute;
	bool AvailableFlag = true;
	vector<int> AssignedSpectralSection;

	// Miss the procedure to extract event from event queue
	// 
	//
	//
	//
	//
	//

	CircuitRoute = routingTable.get_shortest_path (circuitRequest->Src, circuitRequest->Dest);

	check_availability_source (CircuitRoute[0], CircuitRoute[1]);

	for (int i = 0; i < SourceAvailableSections.size (); i++) {
		for (int j = 2; j < CircuitRoute.size (); j++) {
			check_availability_link (CircuitRoute[j - 1], CircuitRoute[j], i, &AvailableFlag);
			if (AvailableFlag == false) break;
		}
		if (AvailableFlag == true) {
			AssignedSpectralSection = SourceAvailableSections[i];				
			for (int i = 1; i < CircuitRoute.size (); i++) {
				for (int k = AssignedSpectralSection[0]; k < AssignedSpectralSection[1]; k++) {
					network->SpectralSlots[i - 1][i][k] = true;	
				}
			}
		}
	}

	CircuitRelease * circuitRelease;
	circuitRelease = new CircuitRelease (CircuitRoute, AssignedSpectralSection, event->StartTime + event->Duration);
}


void ResourceAssignment::handle_releases () {
	// Missing the percedure to extract event
	//
	//
	//
	//
	//
	//
	for (int i = 1; i < event->CircuitRoute.size (); i++) {
		for (int k = event->OccupiedSpectralSlots[0]; k < event->OccupiedSpectralSlots[1]; k++) {
			network->SpectralSlots[i - 1][i][k] = false;	
		}
	}
}

	
	

