#ifndef BIN_H
#define BIN_H

#include "configuration.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int binId;
    int encoderTickStart;
    int encoderTickEnd;
    bool binStatus;
    float binFullness;
    int binNextEntryPoint;
} Bin;

void initializeBins(Bin *bins);

#endif /* BIN_H */
