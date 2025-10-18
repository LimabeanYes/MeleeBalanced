#include "cap.h"
#include "math.h"

void specialN_PhysCallback(GOBJ* gobj) {
	void (*cb)(GOBJ * gobj) = (void*)0x800E2F2C;
	cb(gobj);
	FighterData* fighter_data = gobj->userdata;

	SpecialNVar* state_var = &fighter_data->state_var;
	SpecialNFlag* script_flags = &fighter_data->ftcmd_var;
	

	if (fighter_data->state.frame == 1) {
		state_var->speed = sqrtf(pow(fighter_data->phys.self_vel.X, 2) + pow(fighter_data->phys.self_vel.Y, 2));

		//OSReport("Speed: %f\n", state_var->speed);
	}
	
	if (fighter_data->state.frame > 51 && fighter_data->state.frame < 58) {

		ftHit* hit0 = &fighter_data->hitbox[0];
		ftHit* hit1 = &fighter_data->hitbox[1];
		ftHit* hit2 = &fighter_data->hitbox[2];
		Fighter_UpdateHitboxDamage(hit0, (27 * state_var->speed), gobj);
		Fighter_UpdateHitboxDamage(hit1, (25 * state_var->speed), gobj);
		Fighter_UpdateHitboxDamage(hit2, (23 * state_var->speed), gobj);

	}
	return;
}

void specialN_AnimCallback(GOBJ* gobj) {
	void (*cb)(GOBJ * gobj) = (void*)0x800E2C80;
	cb(gobj);
	FighterData* fighter_data = gobj->userdata;

	SpecialNVar* state_var = &fighter_data->state_var;
	SpecialNFlag* script_flags = &fighter_data->ftcmd_var;

	float speed = 0.1;
	if (fighter_data->state.frame == 0) {

		speed = fighter_data->phys.self_vel.X;
	}

	if (fighter_data->state.frame == 0) {

		speed = fighter_data->phys.self_vel.X;
		
		//ActionStateChange(fighter_data->state.frame, state_var->speed, 0, gobj, 348, 0x340611, 0);
		Fighter_SetAnimRate(gobj, fighter_data->phys.self_vel.X);
	}
	return;
}
void specialAirN_AnimCallback(GOBJ* gobj) {
	void (*cb)(GOBJ * gobj) = (void*)0x800E2D5C;
	cb(gobj);
	FighterData* fighter_data = gobj->userdata;

	SpecialNVar* state_var = &fighter_data->state_var;
	SpecialNFlag* script_flags = &fighter_data->ftcmd_var;

	float speed = 0.1;
	if (fighter_data->state.frame == 0) {

		speed = fighter_data->phys.self_vel.X;
	}
	if (fighter_data->state.frame == 0) {

		speed = fighter_data->phys.self_vel.X;

		//ActionStateChange(fighter_data->state.frame, state_var->speed, 0, gobj, 348, 0x340611, 0);
		Fighter_SetAnimRate(gobj, fighter_data->phys.self_vel.X);
	}
	return;
}
void specialAirN_PhysCallback(GOBJ* gobj) {
	void (*cb)(GOBJ * gobj) = (void*)0x800E3018;
	cb(gobj);
	FighterData* fighter_data = gobj->userdata;

	SpecialNVar* state_var = &fighter_data->state_var;
	SpecialNFlag* script_flags = &fighter_data->ftcmd_var;
	
	if (fighter_data->state.frame == 1) {
		state_var->speed = sqrtf( pow(fighter_data->phys.self_vel.X,2) + pow(fighter_data->phys.self_vel.Y,2));
		
		//OSReport("Speed: %f\n", state_var->speed);
	}
	

	if (fighter_data->state.frame > 51) {
		//OSReport("MEH: %f\n", speed);
		ftHit* hit0 = &fighter_data->hitbox[0];
		ftHit* hit1 = &fighter_data->hitbox[1];
		ftHit* hit2 = &fighter_data->hitbox[2];
		Fighter_UpdateHitboxDamage(hit0, (27 * state_var->speed), gobj);
		Fighter_UpdateHitboxDamage(hit1, (25 * state_var->speed), gobj);
		Fighter_UpdateHitboxDamage(hit2, (23 * state_var->speed), gobj);
	}


	return;
}