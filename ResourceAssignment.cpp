/**************************************************
 * First-Fit  
 **************************************************/
#define DEBUG_print_resource_state_on_the_path
// #define DEBUG_in_check_availability_link
#define DEBUG_print_SourceAvailableSections
#define DEBUG_collect_EventID_of_blocked_requests //Need to collaberate with DEBUG_print_EventID_of_blocked_requests

#define LOCK_use_Modulation_Formats

#ifdef LOCK_use_Modulation_Formats
#include "ModulationFormats.h"
#endif

#include <iostream>
#include "ResourceAssignment.h"
#include <string>
 

//Used event to represent Event instance
void ResourceAssignment::check_availability_source (unsigned int predecessor, unsigned int successor, CircuitRequest * circuitRequest) {
	bool AvailableFlag = true;
	vector<int> HSourceAvailableSections;

	SourceAvailableSections.clear ();
	for (int i = 0; i < (NumofSpectralSlots - circuitRequest->OccupiedSpectralSlots + 1); i++) {
		AvailableFlag = true;
		if (network->SpectralSlots[predecessor][successor][i] == false) {
			for (int j = 0; j < circuitRequest->OccupiedSpectralSlots; j++) {
				if (network->SpectralSlots[predecessor][successor][i + j] == true) {
					i = i + j;//not i = i + j + 1, because there is a i++ for the loop
					AvailableFlag = false;
					break;	
				}
			}

			if (AvailableFlag == true) {
				HSourceAvailableSections.push_back (i);	
				HSourceAvailableSections.push_back (i + circuitRequest->OccupiedSpectralSlots - 1);
				SourceAvailableSections.push_back (HSourceAvailableSections);
				HSourceAvailableSections.clear ();	
			}
		}
	}
}


//Used event to represent Event instance
void ResourceAssignment::check_availability_link (unsigned int predecessor, unsigned int successor, int i, bool * AvailableFlag, int * TempLocation) {

	#ifdef DEBUG_in_check_availability_link
	cout << "The checked link is between node " << predecessor << " and " << successor << endl; 
	cout << "The checked SpectralSlots are between  " << SourceAvailableSections[i][0] << " and " << SourceAvailableSections[i][1] << endl;
	#endif 

	for (int j = SourceAvailableSections[i][0]; j < SourceAvailableSections[i][1] + 1; j++) {
		#ifdef DEBUG_in_check_availability_link
		cout << network->SpectralSlots[predecessor][successor][j] << ' ';
		#endif

		if (network->SpectralSlots[predecessor][successor][j] == true) {
			* TempLocation = j;
			* AvailableFlag = false;
			break;	
		}	
	}

	#ifdef DEBUG_in_check_availability_link
	cout << endl;
	#endif
}


void ResourceAssignment::handle_requests (CircuitRequest * circuitRequest) {
	RoutingTable routingTable (network);	

	vector<int> CircuitRoute;
	bool AvailableFlag = true;
	vector<int> AssignedSpectralSection (2, -1);
	string MF = "BPSK";
	int TempLocation = -1;

	CircuitRoute = routingTable.get_shortest_path (circuitRequest->Src, circuitRequest->Dest);

	#ifdef DEBUG_print_resource_state_on_the_path
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	for (int i = 0; i < CircuitRoute.size (); i++) {
		cout << CircuitRoute[i] << ' ';
	}
	cout << endl;
	cout << "PRINT resources status BEFORE Allocation" << endl;
	for (int i = 1; i < CircuitRoute.size (); i++) {
		cout << "On link " << CircuitRoute[i-1] << " to " << CircuitRoute[i] << endl;
		for (int j = 0; j < NumofSpectralSlots; j++) {
			cout <<  network->SpectralSlots[CircuitRoute[i - 1]][CircuitRoute[i]][j] << ' ';
		}
		cout << endl;
	}
	#endif

	unsigned int DS;
	#ifdef LOCK_use_Modulation_Formats
	ModulationFormats modulationFormats (circuitRequest, network);
	MF = modulationFormats.mf_chosen (CircuitRoute, &circuitRequest->OccupiedSpectralSlots, &DS);
	#endif
	circuitRequest->OccupiedSpectralSlots += GB;

	// Calculate possible SpectralSlotSections on the link between source and its successor
	check_availability_source (CircuitRoute[0], CircuitRoute[1], circuitRequest);

	#ifdef DEBUG_print_SourceAvailableSections
	cout << "PRINT Source Available Sections" << endl;
	for (int i = 0; i < SourceAvailableSections.size (); i++) {
		for (int j = 0; j < SourceAvailableSections[i].size (); j++) {
			cout << SourceAvailableSections[i][j] << ' ';
		}
		cout << '\t';
	}
	cout << endl;
	#endif
 
	// Loop for all the possible SpectralSlotSections on the link between source and its successor
	if (SourceAvailableSections.empty ()) AvailableFlag = false;
	else {
		for (int i = 0; i < SourceAvailableSections.size (); i++) {
			AvailableFlag = true;

			if (TempLocation >= SourceAvailableSections[i][0]) {
				AvailableFlag = false;
				continue;
			}
			// if (TempFlag == false)
			// 	continue;

			// Loop to check if the selected SpectalSlotSection on source is available for all the following links on the path
			for (int j = 2; j < CircuitRoute.size (); j++) {
				// For each link on the path, check if the selected SpectralSlotSection available on the selected link
				check_availability_link (CircuitRoute[j - 1], CircuitRoute[j], i, &AvailableFlag, &TempLocation);
				// if the AvailableFlag is false, the selected SpectralSlotSecton is not available on the selected link
				if (AvailableFlag == false) break;
			}
			if (AvailableFlag == true) {
				AssignedSpectralSection.at (0) = SourceAvailableSections[i][0];
				AssignedSpectralSection.at (1) = SourceAvailableSections[i][1];
				for (int i = 1; i < CircuitRoute.size (); i++) {
					for (int k = AssignedSpectralSection[0]; k < AssignedSpectralSection[1] + 1; k++) {
						network->SpectralSlots[CircuitRoute[i - 1]][CircuitRoute[i]][k] = true;
					}
				}
				break;
			}
		}
		
	}

	if (AvailableFlag == false) {
		network->NumofDoneRequests++;

		#ifdef DEBUG_collect_EventID_of_blocked_requests
		network->BlockedRequests.push_back (circuitRequest->EventID);
		#endif

		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
		cout << "Request " << circuitRequest->EventID << " is blocked" << endl;
		cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^" << endl;
		network->NumofFailedRequests++;
	}
	else if (AvailableFlag == true) {
		cout << "------------------------------------------------------------" << endl;
		cout << "Request ID: " << circuitRequest->EventID << "\tStart: " << circuitRequest->EventTime << "\tEnd: " << circuitRequest->StartTime + circuitRequest->Duration << endl;
		cout << "Source: " << circuitRequest->Src << "  Destination: " << circuitRequest->Dest << "  ModulationFormats: " << MF << endl;
		cout << "Path: ";
		for(unsigned int t = 0; t < CircuitRoute.size()-1; t++)
			cout << CircuitRoute.at(t) << " --> ";
		cout << CircuitRoute.at (CircuitRoute.size() - 1) << endl;
		cout << "The allocated Spectral Section is from slot " << AssignedSpectralSection[0] << " to " << AssignedSpectralSection[1] << endl; 
		cout << "------------------------------------------------------------" << endl;

		CircuitRelease * circuitRelease;
		circuitRelease = new CircuitRelease (circuitRequest->EventID, CircuitRoute, AssignedSpectralSection, circuitRequest->StartTime + circuitRequest->Duration);
		eventQueue->queue_insert (circuitRelease);

		network->NumofAllocatedRequests++;
	}

	#ifdef DEBUG_print_resource_state_on_the_path
	for (int i = 0; i < CircuitRoute.size (); i++) {
		cout << CircuitRoute[i] << ' ';
	}
	cout << endl;
	cout << "PRINT resources state AFTER Allocation" << endl;
	for (int i = 1; i < CircuitRoute.size (); i++) {
		cout << "On link " << CircuitRoute[i-1] << " to " << CircuitRoute[i] << endl;
		for (int j = 0; j < NumofSpectralSlots; j++) {
			cout <<  network->SpectralSlots[CircuitRoute[i - 1]][CircuitRoute[i]][j] << ' ';
		}
		cout << endl;
	}
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << endl;
	#endif
}


void ResourceAssignment::handle_releases (CircuitRelease * circuitRelease) {
	#ifdef DEBUG_print_resource_state_on_the_path
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	for (int i = 0; i < circuitRelease->CircuitRoute.size (); i++) {
		cout << circuitRelease->CircuitRoute[i] << ' ';
	}
	cout << endl;
	cout << "PRINT resources status BEFORE Release" << endl;
	for (int i = 1; i < circuitRelease->CircuitRoute.size (); i++) {
		cout << "On link " << circuitRelease->CircuitRoute[i-1] << " to " << circuitRelease->CircuitRoute[i] << endl;
		for (int j = 0; j < NumofSpectralSlots; j++) {
			cout <<  network->SpectralSlots[circuitRelease->CircuitRoute[i - 1]][circuitRelease->CircuitRoute[i]][j] << ' ';
		}
		cout << endl;
	}
	#endif

	for (int i = 1; i < circuitRelease->CircuitRoute.size (); i++) {
		for (int k = circuitRelease->OccupiedSpectralSection[0]; k < circuitRelease->OccupiedSpectralSection[1] + 1; k++) {
			network->SpectralSlots[circuitRelease->CircuitRoute[i - 1]][circuitRelease->CircuitRoute[i]][k] = false;	
		}
	}
	
	network->NumofDoneRequests++;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;
	cout << "Release Event: " << circuitRelease->EventID << "\tTime: " << circuitRelease->EventTime << endl;
	cout << "The released Spectral Section is from " << circuitRelease->OccupiedSpectralSection[0] << " to " << circuitRelease->OccupiedSpectralSection[1] << endl;
	cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << endl;

	#ifdef DEBUG_print_resource_state_on_the_path
	for (int i = 0; i < circuitRelease->CircuitRoute.size (); i++) {
		cout << circuitRelease->CircuitRoute[i] << ' ';
	}
	cout << endl;
	cout << "PRINT resources AFTER Release" << endl;
	for (int i = 1; i < circuitRelease->CircuitRoute.size (); i++) {
		cout << "On link " << circuitRelease->CircuitRoute[i-1] << " to " << circuitRelease->CircuitRoute[i] << endl;
		for (int j = 0; j < NumofSpectralSlots; j++) {
			cout <<  network->SpectralSlots[circuitRelease->CircuitRoute[i - 1]][circuitRelease->CircuitRoute[i]][j] << ' ';
		}
		cout << endl;
	}
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << endl;
	#endif
}

	
