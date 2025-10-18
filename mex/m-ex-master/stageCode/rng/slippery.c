#include "rng.h"

void randEvent_slippery_Apply() {
	for (int i = 0; i < 4; i++) {
		GOBJ* fighter = Fighter_GetGObj(i);
		if (fighter) {
			FighterData* fd = fighter->userdata;
			ogAttribute[i] = fd->attr.ground_friction;
			fd->attr.ground_friction *= gr_param->slippery_attributes.friction_multiplier;
		}
	}
	return;
}

void randEvent_slippery_Kill() {
	for (int i = 0; i < 4; i++) {
		GOBJ* fighter = Fighter_GetGObj(i);
		if (fighter) {
			FighterData* fd = fighter->userdata;
			fd->attr.ground_friction = ogAttribute[i];
		}
	}
	return;
}