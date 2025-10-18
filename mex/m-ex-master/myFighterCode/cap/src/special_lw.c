#include "cap.h"

void ToadAwsom_JumpIasa(GOBJ* gobj) {
    if (Fighter_IASACheck_JumpF(gobj)) {
        ActionStateChange(0, 1, 0, gobj, ASID_KNEEBEND, 0x0, 0);
    }
}

void ToadAwsom_JumpAirIasa(GOBJ* gobj) {
    FighterData* fighter_data = gobj->userdata;
    if (fighter_data->phys.air_state == 1 && Fighter_IASACheck_JumpAerial(gobj)) {
        Fighter_EnterJumpAerial(gobj);
    }
}

void specialLw_IasaCb(GOBJ* gobj) {
	ToadAwsom_JumpIasa(gobj);
	return;
}