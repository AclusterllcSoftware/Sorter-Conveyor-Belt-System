#ifndef BOX_H
#define BOX_H

#include "configuration.h"

#include <stdio.h>
#include <stdbool.h>


typedef struct {
    float width;
    float length;
    float height;
    float weight;
    int code;
    int destinationBin[4];
    int binEntryPosition;
    float GGLocationX;
    float GGLocationY;
    float leadingGap;
    float trailingGap;
    bool sentToBinStatus;
    ErrorCode rejectCode;
    int currentLocationEncoderTick;
    int boxEntryEncoderTick;
    int currentDivertID;
    int divertsPosition[MAX_DIVERT_NUMBER];
} Box;

bool detectedBoxbyPESensor();
void setBoxParameters(Box *box);
void preprocessBeforeEnqueueBox(Box *newBox);
bool checkBoxDimensions(const Box *box);
bool checkGeoLocation(const Box *box);
bool checkLeadingGapAndTrailingGap(const Box *box);
bool resolveLeadingAndTrailingGap(Box *box);
void calculateDestinationBin(Box *box);
void calculateDivertToBeUsed(Box *box);
void setBoxEntryEncoderTick(Box *box, int currentEncoderTick);

#endif /* BOX_H */

