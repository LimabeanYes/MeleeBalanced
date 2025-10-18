#include "cap.h"


void specialHi_hitAnimCb(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	fd->jump.jumps_used = 0;
	Fighter_SetAnimRate(gobj, 2);
	if (FrameTimerCheck(gobj) == 0) {
		Fighter_EnterFall(gobj);
	}
	return;
}

void specialHi_hit1Coll(GOBJ* gobj) {
	void (*unk)(GOBJ * someGobj) = (int*)0x800E54B8;
	unk(gobj);
	FighterData* fighter_data = gobj->userdata;
	for (int i = 0; i < 2; i++) {
		ftHit* hit = &fighter_data->throw_hitbox[i];

		if (fighter_data->phys.air_state == 0) {
			hit->angle = 270;
		}
		else {
			hit->angle = 90;
		}
	}
}
void specialHi_hit2Coll(GOBJ* gobj) {
	void (*unk)(GOBJ * someGobj) = (int*)0x800E49DC;
	unk(gobj);
	FighterData* fighter_data = gobj->userdata;
		for (int i = 0; i < 2; i++) {
			ftHit* hit = &fighter_data->throw_hitbox[i];
			
			if (fighter_data->phys.air_state == 0) {
				hit->angle = 270;
			}
			else {
				hit->angle = 90;
			}
		}
}