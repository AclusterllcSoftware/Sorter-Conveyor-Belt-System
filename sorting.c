
#include "sorting.h"

// Function to get the current encoder tick (for simulation purposes)
int getCurrentEncoderTick() {
    static int tick = 0;
    return tick++;
}


// Function to process sorting of boxes and sending them to bins
void boxSortingProcess(ConveyorQueue *conveyorQueue, int currentEncoderTick, Bin *bins, Divert *diverts) {
    // Iterate through the conveyor queue
    for (int i = conveyorQueue->front; i != (conveyorQueue->rear + 1) % MAX_CONVEYOR_CAPACITY; i = (i + 1) % MAX_CONVEYOR_CAPACITY) {
        Box *currentBox = conveyorQueue->boxes[i];

				// Check if it's time to activate the current divert of the current box
        if (diverts[currentBox->currentDivertID].divertLengthTick == currentEncoderTick) { // todo:: check divert status
            if (currentBox->divertsPosition[currentBox->currentDivertID] != diverts[currentBox->currentDivertID].currentPosition) {
                // do some function to active divert 

								// update current divert position
                diverts[currentBox->currentDivertID].currentPosition = currentBox->divertsPosition[currentBox->currentDivertID];
               
							  printf("Divert %d activated for Box %d.\n", currentBox->currentDivertID, currentBox->code);
            }
            currentBox->currentDivertID++;
        }

				// Skip processing if the box has already been sent to a bin
        if (currentBox->sentToBinStatus) {
            continue;
        }

        // Check if the box is ready to be sent to a bin
        if (currentEncoderTick == currentBox->boxEntryEncoderTick + currentBox->binEntryPosition) {
            // Determine the destination bin
            int destinationBin = currentBox->destinationBin[0]; // Assuming first destination bin

            // Check if the destination bin is not full
            if (bins[destinationBin].binFullness < BIN_FULL_MAX) {
                // Send the box to the bin
                currentBox->sentToBinStatus = true;
                printf("Box %d sent to bin %d.\n", currentBox->code, destinationBin);
                
                // Increment binFullness
                bins[destinationBin].binFullness++;
            } else {
                // Find the next available destination bin
                for (int j = 1; j < 4; j++) { // Start from second destination bin
                    destinationBin = currentBox->destinationBin[j];
                    if (bins[destinationBin].binFullness < BIN_FULL_MAX) {
                        // Update the destination bin and bin entry position
                        currentBox->destinationBin[0] = destinationBin;
                        currentBox->binEntryPosition = bins[destinationBin].encoderTickStart - currentEncoderTick;
                        printf("Box %d redirected to bin %d due to bin fullness.\n", currentBox->code, destinationBin);
                        break;
                    }
                }
            }
        }

    }
}


