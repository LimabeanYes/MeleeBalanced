#include "bowser.h"

void specialLw_IASACallback(GOBJ* gobj) {
	FighterData* fighter_data = gobj->userdata;

	if (fighter_data->phys.air_state == 1 && fighter_data->ftcmd_var.flag2==1 && Fighter_IASACheck_JumpAerial(gobj)) {
		Fighter_EnterJumpAerial(gobj);
	}
	return;
}

void specialAirLw_IASACallback(GOBJ* gobj) {
	FighterData* fighter_data = gobj->userdata;
	//float lstick_y = fighter_data->input.lstick.Y;
	//bool checkup = lstick_y > 0;
	
	if (fighter_data->phys.air_state == 1 && fighter_data->ftcmd_var.flag2 == 1 && Fighter_IASACheck_JumpAerial(gobj)) {
		Fighter_EnterJumpAerial(gobj);
	}
	return;
}

void specialLwLanding_AnimCB(GOBJ* gobj) {
	
	void (*cb)(GOBJ * gobj) = (void*)0x801349C4;
	cb(gobj);
	FighterData* fighter_data = gobj->userdata;
	SpecialLwVar* state_var = Fighter_GetStateVars(gobj);

	if (((fighter_data->input.down & HSD_BUTTON_B) != 0)  && fighter_data->ftcmd_var.flag2 == 0) {
		ActionStateChange(fighter_data->state.frame, 2, 0, gobj, STATE_SPECIALLWLAND, 0, 0);
	}
	return;
}