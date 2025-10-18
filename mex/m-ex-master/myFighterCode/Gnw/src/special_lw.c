#include "gnw.h"

void Gnw_SpecialLw_IASAcb(GOBJ* gobj) {
	FighterData* fighter_data = gobj->userdata;
	
	if (Fighter_CheckJumpInput(gobj) && Fighter_IASACheck_JumpF(gobj)) {
		//Fighter_SetAirborne(fighter_data);
		//Fighter_EnterJumpAerial(gobj);
		ActionStateChange(0, 1, 0, gobj, ASID_KNEEBEND, 0, 0);
	}
	void (*cb)(GOBJ * gobj) = (void*)0x8014D1AC;
	cb(gobj); 
}

void Gnw_SpecialAirLw_IASAcb(GOBJ* gobj) {
	FighterData* fighter_data = gobj->userdata;
	
	if (Fighter_IASACheck_JumpAerial(gobj) && Fighter_CheckJumpInput(gobj)) {
		OSReport("hi\n");
		Fighter_EnterJumpAerial(gobj);
	}
	void (*cb)(GOBJ * gobj) = (void*)0x8014D264;
	cb(gobj);
}
