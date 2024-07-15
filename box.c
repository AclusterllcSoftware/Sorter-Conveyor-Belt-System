#include "box.h"

#include <stdlib.h>
#include <stdio.h>
 
// Function definitions...


// Function to detect box by proximity sensor
bool detectedBoxbyPESensor() {
    // In a real system, this function would detect if a box is present using the proximity sensor
    // For simulation purposes, we return true here to simulate detection of a box
    return true;
}

// Function to set box parameters after detection
void setBoxParameters(Box *box) {
    box->width = 10.0;
    box->length = 20.0;
    box->height = 15.0; 
    box->weight = 5.0;
		static int code = 12;
    box->code = code++;
    box->GGLocationX = 50; // Set default geo-location X
    box->GGLocationY = 50; // Set default geo-location Y
    box->leadingGap = 10.0; // Set default leading gap
    box->trailingGap = 10.0; // Set default trailing gap
    // Set default destination bins with random values
		box->sentToBinStatus = false;
		box->currentDivertID = 0;
    int defaultDestinationBins[4] = {1, 3, 5, 7};
    for (int i = 0; i < 4; ++i) {
        box->destinationBin[i] = defaultDestinationBins[i];
    }
		
		// box->divertsPosition[8] = {1,2,0,1,1,2,0,1}; //MAX_DIVERT_NUMBER
}



// Function to check box dimensions
bool checkBoxDimensions(const Box *box) {
    if (box->width > MAX_WIDE || box->length > MAX_LEN || box->height > MAX_HEIGHT) {
        printf("Error: Box dimensions exceed maximum limit.\n");
        return false;
    }
    return true;
}


// Function to check box geo-location
bool checkGeoLocation(const Box *box) {
    if (box->GGLocationX < MIN_GG_LOCATION_X || box->GGLocationX > MAX_GG_LOCATION_X || box->GGLocationY < MIN_GG_LOCATION_Y || box->GGLocationY > MAX_GG_LOCATION_Y) {
        printf("Error: Box geo-location is invalid.\n");
        return false;
    }
    return true;
}


// Function to check leading and trailing gaps
bool checkLeadingGapAndTrailingGap(const Box *box) {
    if (box->leadingGap < MIN_LEADING_GAP || box->trailingGap < MIN_TRAILING_GAP) {
        printf("Error: Leading gap or trailing gap exceeds minimum limit.\n");
        return false;
    }
    return true;
}


// Function to resolve leading and trailing gaps
bool resolveLeadingAndTrailingGap(Box *box) {
    // Add logic to resolve leading and trailing gaps
    printf("Resolving leading and trailing gaps for Box %d.\n", box->code);
    // For simulation purposes, assume leading and trailing gaps are resolved successfully
    return true;
}


void calculateDestinationBin(Box *box) {
    printf("Calculating destination bins for Box %d.\n", box->code);
    // Set default destination bins with random values
    int defaultDestinationBins[4] = {1, 3, 5, 7};
    for (int i = 0; i < 4; ++i) {
        box->destinationBin[i] = defaultDestinationBins[i];
    }
}


// Function to calculate divert IDs to be used
void calculateDivertToBeUsed(Box *box) {
    // Set divert IDs to be used based on a pattern
    printf("Calculating divert IDs to be used for Box %d.\n", box->code);
    int divertPattern[MAX_DIVERT_NUMBER] = {1, 0, 1, 2, 1, 0, 1, 2}; // Pattern for divert IDs
    for (int i = 0; i < MAX_DIVERT_NUMBER; ++i) {
        box->divertsPosition[i] = divertPattern[i];
    }
}


// Function to set box entry encoder tick
void setBoxEntryEncoderTick(Box *box, int currentEncoderTick) {
    box->boxEntryEncoderTick = currentEncoderTick;
}


// Function to preprocess before enqueuing a box
void preprocessBeforeEnqueueBox(Box *newBox) {
    // Check box dimensions
    if (!checkBoxDimensions(newBox)) {
        newBox->rejectCode = DIMENSION_EXCEED;
        return;
    }

    // Check box geo-location
    if (!checkGeoLocation(newBox)) {
        newBox->rejectCode = GEOLOCATION_INVALID;
        return;
    }

    // Check leading and trailing gaps
    if (!checkLeadingGapAndTrailingGap(newBox)) {
        newBox->rejectCode = LEADING_GAP;
        return;
    }

    // Resolve leading and trailing gaps
    if (!resolveLeadingAndTrailingGap(newBox)) {
        newBox->rejectCode = TRAILING_GAP;
        return;
    }

    // Calculate destination bin for the box
    calculateDestinationBin(newBox);

    // Calculate divert IDs to be used for the box
    calculateDivertToBeUsed(newBox);
}
