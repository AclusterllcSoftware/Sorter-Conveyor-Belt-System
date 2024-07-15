#ifndef CONVEYORQUEUE_H
#define CONVEYORQUEUE_H
#include "configuration.h"
#include "box.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    Box *boxes[MAX_CONVEYOR_CAPACITY];
    int front;
    int rear;
    int count;
} ConveyorQueue;

void initializeConveyorQueue(ConveyorQueue *convQueue);
void enqueueBoxConveyor(ConveyorQueue *conveyorQueue, Box *newBox);
void dequeueBoxConveyor(ConveyorQueue *conveyorQueue);
bool getFrontBoxSentToBinStatus(ConveyorQueue *conveyorQueue);
void boxDetectAndInitializationProcess(ConveyorQueue *conveyorQueue, int currentEncoderTick);

#endif /* CONVEYORQUEUE_H */
