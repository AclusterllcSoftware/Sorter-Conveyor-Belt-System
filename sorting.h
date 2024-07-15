#ifndef SORTING_H
#define SORTING_H

#include "configuration.h"
#include "bin.h"
#include "box.h"
#include "conveyorQueue.h"
#include "divert.h"

#include <stdio.h>
#include <stdbool.h>

int getCurrentEncoderTick();
void boxSortingProcess(ConveyorQueue *conveyorQueue, int currentEncoderTick, Bin *bins, Divert *diverts);

#endif /* SORTING_H */