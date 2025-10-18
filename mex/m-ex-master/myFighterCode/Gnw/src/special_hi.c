#include "gnw.h"

void Gnw_SpecialHi_IASAcb(GOBJ* gobj) {
	FighterData* fighter_data = gobj->userdata;
	void (*cb)(GOBJ * gobj) = (void*)0x8014E290;
	cb(gobj);
	if (((fighter_data->input.down & HSD_BUTTON_B) != 0)) {
		fighter_data->phys.self_vel.Y = fighter_data->phys.self_vel.Y / SPECIALHI_CANCEL_MOMENTUM_DIVISOR;
		Fighter_EnterSpecialFall(gobj, 1, 0, 0, 0.5, 14);
	}
}

void Gnw_SpecialAirHi_IASAcb(GOBJ* gobj) {
	FighterData* fighter_data = gobj->userdata;
	void (*cb)(GOBJ * gobj) = (void*)0x8014E2B0;
	cb(gobj);
	if (((fighter_data->input.down & HSD_BUTTON_B) != 0)) {
		fighter_data->phys.self_vel.Y = fighter_data->phys.self_vel.Y / SPECIALHI_CANCEL_MOMENTUM_DIVISOR;
		Fighter_EnterSpecialFall(gobj, 1, 0, 0, 0.5, 14);
	}
}

void Gnw_SpecialHi_PhysCb(GOBJ* gobj) {
	FighterData* fighter_data = gobj->userdata;
	void (*cb)(GOBJ * gobj) = (void*)0x8014E374;
	cb(gobj);
	if (((fighter_data->input.down & HSD_BUTTON_B) != 0)) {
		fighter_data->phys.self_vel.Y = fighter_data->phys.self_vel.Y / SPECIALHI_CANCEL_MOMENTUM_DIVISOR;
	}
}

void Gnw_SpecialAirHi_PhysCb(GOBJ* gobj) {
	FighterData* fighter_data = gobj->userdata;
	void (*cb)(GOBJ * gobj) = (void*)0x8014E394;
	cb(gobj);
	if (((fighter_data->input.down & HSD_BUTTON_B) != 0)) {
		fighter_data->phys.self_vel.Y = fighter_data->phys.self_vel.Y / SPECIALHI_CANCEL_MOMENTUM_DIVISOR;
	}
}