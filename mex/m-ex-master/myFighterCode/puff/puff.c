#include "mex.h"


void dmg_kb(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	if (!((fd->state_id >= ASID_CATCH && fd->state_id <= ASID_BARRELCANNONWAIT) || //avoid certain icky states
		(fd->state_id >= ASID_DEADDOWN && fd->state_id <= ASID_REBIRTHWAIT))) {
		int rand = HSD_Randi(2000);
		if (rand == 1) {
			Fighter_EnterSpecialFall(gobj, 1, 0, 1, 1.1, 20);
		}
	}
	
	if (HSD_Randi((int)(fd->dmg.percent*0.5)) == 1) {
		Fighter_GiveDamage(fd, 5);
	}
}

void onFrame(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	if (fd->phys.air_state != 0) {
		dmg_kb(gobj);
	}
}