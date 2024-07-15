#include "divert.h"


// Initialize diverts
void initializeDiverts(Divert *diverts)
{
	for (int i = 0; i < MAX_DIVERT_NUMBER; ++i) {
			diverts[i].id = i;
			diverts[i].location = i; // Example location initialization
			diverts[i].divertLengthTick = 1000 * i; // Example divert length tick initialization
			diverts[i].currentPosition = 0; // Initialize currentPosition to 0 (0,1,2)
			diverts[i].activateStatus = false; // Initialize activateStatus to false
	}
}
