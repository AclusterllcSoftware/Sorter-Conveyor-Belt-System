#ifndef DIVERT_H
#define DIVERT_H
#include "configuration.h"
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id;
    int location;
    int divertLengthTick;
    int currentPosition;
    bool activateStatus;
} Divert;

void initializeDiverts(Divert *diverts);

#endif /* DIVERT_H */
