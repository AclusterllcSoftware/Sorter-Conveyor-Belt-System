#include "bin.h"




// Function to initialize bins with default values
void initializeBins(Bin *bins) {
    // Initialize each bin with default values
    for (int i = 0; i < MAX_BINS; ++i) {
        bins[i].binId = i + 1;
        bins[i].encoderTickStart = (i * BIN_ENCODER_TICKS) + 1;
        bins[i].encoderTickEnd = (i + 1) * BIN_ENCODER_TICKS;
        bins[i].binStatus = false; // Bin status initially set to false (not full)
        bins[i].binFullness = 0.0; // Bin fullness initially set to 0%
        bins[i].binNextEntryPoint = (i + 1) % MAX_BINS; // Initialize bin next entry point
    }
}