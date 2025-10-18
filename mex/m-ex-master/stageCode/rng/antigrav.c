#include "rng.h"

void randEvent_Antigravity_Kill() {
	for (int i = 0; i < 4; i++) {
		GOBJ* fighter = Fighter_GetGObj(i);
		if (fighter) {
			FighterData* fd = fighter->userdata;
			fd->attr.gravity = ogAttribute[i];
		}
	}
}

void randEvent_Antigravity_Apply() {
	for (int i = 0; i < 4; i++) {
		GOBJ* fighter = Fighter_GetGObj(i);
		if (fighter) {
			FighterData* fd = fighter->userdata;
			ogAttribute[i] = fd->attr.gravity;
			fd->attr.gravity = gr_param->antigrav_attributes.antigrav_strength;
		}
	}
}
