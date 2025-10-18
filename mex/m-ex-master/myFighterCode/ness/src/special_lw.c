#include "ness.h"

void SpecialLwStart_IASACallback(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	if (Fighter_CheckJumpInput(gobj) != 0 && Fighter_IASACheck_JumpF(gobj)) {
		Fighter_SetAirborne(fd);
		ActionStateChange(0, 1, 0, gobj, ASID_KNEEBEND, 0x0, 0);
	}
	void (*cb)(GOBJ * gobj) = (void*)0x8011A0E0;
	cb(gobj);
}
void SpecialLwHold_IASACallback(GOBJ* gobj) {
	void (*cb)(GOBJ * gobj) = (void*)0x8011A438;
	cb(gobj);
	FighterData* fd = gobj->userdata;
	if (Fighter_CheckJumpInput(gobj) != 0 && Fighter_IASACheck_JumpF(gobj)) {
		Fighter_SetAirborne(fd);
		ActionStateChange(0, 1, 0, gobj, ASID_KNEEBEND, 0x0, 0);
	}
}

void SpecialAirLwStart_IASACallback(GOBJ* gobj) {
	if (Fighter_CheckJumpInput(gobj) != 0 && Fighter_IASACheck_JumpAerial(gobj) != 0) {
		//Fighter_EnterJumpAerial(gobj);
		void (*cb2)(GOBJ * gobj) = (void*)0x800CBD18;
		cb2(gobj);
	}
	void (*cb)(GOBJ * gobj) = (void*)0x8011A0E4;
	cb(gobj);
}
void SpecialAirLwHold_IASACallback(GOBJ* gobj) {
	if (Fighter_CheckJumpInput(gobj) != 0 && Fighter_IASACheck_JumpAerial(gobj) != 0) {
		//Fighter_EnterJumpAerial(gobj);
		void (*cb2)(GOBJ * gobj) = (void*)0x800CBD18;
		cb2(gobj);
	}
	void (*cb)(GOBJ * gobj) = (void*)0x8011A43C;
	cb(gobj);
}