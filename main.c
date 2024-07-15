#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

 #include "configuration.h"
#include "bin.h"
#include "box.h"
#include "conveyorQueue.h"
#include "divert.h"
#include "sorting.h"

// Main function...




int main() {

		// Initialize bins
    Bin bins[MAX_BINS];
    initializeBins(bins);

		// Initialize diverts
		Divert diverts[MAX_DIVERT_NUMBER];
		initializeDiverts(diverts);


    // Initialize conveyor queue
    ConveyorQueue conveyorQueue;
		initializeConveyorQueue(&conveyorQueue);
    
		int currentEncoderTick;

    // Simulated loop for continuous arrival of boxes on the conveyor belt
    while (true) {

				 // Get the current encoder tick
        currentEncoderTick = getCurrentEncoderTick();

				// Detect boxes by proximity sensor and initialize them
        boxDetectAndInitializationProcess(&conveyorQueue, currentEncoderTick);

				// Call box sorting process to divert boxes to the bin if conditions are met
				boxSortingProcess(&conveyorQueue, currentEncoderTick, bins, diverts);

				// Check if the front box in the conveyor queue has been sent to the bin
    		if (getFrontBoxSentToBinStatus(&conveyorQueue)) {
					// Dequeue the front box from the conveyor queue
					printf("front Box sent to bin and will be removed from queue\n"); 
					dequeueBoxConveyor(&conveyorQueue);
    		}

        sleep(10);
    }

    return 0;
}
