#include "toad.h"
#include <stdarg.h>

//put debug related stuff here maybe?

void CheckLevel_debug() {
	if (IS_DEBUG < 0 || IS_DEBUG > 3) {
		OSReport("Error: Debug level out of range lol. Keep it from 0-3\n");
		__assert("toad.c", 24, 0);
		return;
	}
}

void setupMeter_debug(int debugMessage) {
	if (IS_DEBUG <= 2) {
		return;
	}
	switch (debugMessage) {
	case 0:
		OSReport("Report: looking for file %s\n", METER_FILENAME);
		break;
	case 1:
		OSReport("Report: found file!\n");
		break;
	case 2:
		OSReport("Report: find symbol %s\n", METER_SYMBOL);
		break;
	case 3:
		OSReport("Report: found symbol %s\n");
		break;
	case 4:
		OSReport("Report: meter gobj setup successful\n");
		break;
	case 5:
		OSReport("Setup completed!\n");
		break;
	}
}