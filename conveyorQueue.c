#include "conveyorQueue.h"

#include <stdio.h>
#include <stdlib.h>
 
// Function definitions...


// initialize conveyorQueue
void initializeConveyorQueue(ConveyorQueue *convQueue)
{
	convQueue->front = -1;
    convQueue->rear = -1;
    convQueue->count = 0;
}



// Function to enqueue a new box onto the conveyor queue
void enqueueBoxConveyor(ConveyorQueue *conveyorQueue, Box *newBox) {
    
    if(newBox->rejectCode != NO_ERROR)
    {
        printf("the box has reject code. sent to rejection bin \n");
        return;
    }
    // Check if the conveyor queue is full
    if ( conveyorQueue->count ==  MAX_CONVEYOR_CAPACITY) {
        printf("Conveyor belt is full. Cannot add more boxes.\n");
        return;
    }

		// Check if the conveyor queue is empty
    if (conveyorQueue->count == 0) {
       conveyorQueue->front = 0;
    }
    // Enqueue the new box onto the conveyor queue
    conveyorQueue->rear = (conveyorQueue->rear + 1) % MAX_CONVEYOR_CAPACITY;
    conveyorQueue->boxes[conveyorQueue->rear] = newBox;
    conveyorQueue->count++;
    printf("Box %d added to conveyor belt.\n", newBox->code);
}


// Function to dequeue a box from the conveyor queue
void dequeueBoxConveyor(ConveyorQueue *conveyorQueue) {
    // Check if the conveyor queue is empty
    if (conveyorQueue->count == 0) {
        printf("Conveyor belt is empty. No boxes to dequeue.\n");
        return;
    }

    // Get the box from the front of the queue
    Box *dequeuedBox = conveyorQueue->boxes[conveyorQueue->front];

    // Move the front pointer to the next box
    if (conveyorQueue->front == conveyorQueue->rear) {
        // If there's only one box in the queue
        conveyorQueue->front = -1;
        conveyorQueue->rear = -1;
    } else {
        conveyorQueue->front = (conveyorQueue->front + 1) % MAX_CONVEYOR_CAPACITY;
    }

    conveyorQueue->count--;
    printf("Box %d dequeued from conveyor belt.\n", dequeuedBox->code);

    // Free memory allocated for the dequeued box
    free(dequeuedBox);
}



// Function to get the sentToBinStatus value of the front box in the conveyor queue
bool getFrontBoxSentToBinStatus(ConveyorQueue *conveyorQueue) {
    // Check if the conveyor queue is empty
    if (conveyorQueue->count == 0) {
        printf("Conveyor belt is empty. No boxes available.\n");
        return false; // Return false if queue is empty
    }

    // Retrieve the front box from the queue
    Box *frontBox = conveyorQueue->boxes[conveyorQueue->front];

    // Return the sentToBinStatus value of the front box
    return frontBox->sentToBinStatus;
}




void boxDetectAndInitializationProcess(ConveyorQueue *conveyorQueue, int currentEncoderTick) {
    // If box is detected by proximity sensor
    if (detectedBoxbyPESensor()) {
        // If there's space on the conveyor belt
        if (conveyorQueue->count < MAX_CONVEYOR_CAPACITY) {
            // Create a new box
            Box *newBox = (Box *)malloc(sizeof(Box));

            // Set box entry encoder tick
            setBoxEntryEncoderTick(newBox, currentEncoderTick);

            // Set box parameters after detection
            setBoxParameters(newBox);

            // Preprocess before enqueuing the box
            preprocessBeforeEnqueueBox(newBox);

            // Enqueue the new box onto the conveyor queue
            enqueueBoxConveyor(conveyorQueue, newBox);

            

			if (newBox != NULL) {
        			free(newBox);
    		}
        } else {
            printf("Conveyor belt is full. Cannot add more boxes.\n");
        }
    }

    
}