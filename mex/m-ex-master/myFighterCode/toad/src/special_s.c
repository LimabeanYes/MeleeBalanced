#include "toad.h"
////////////////////////
//  Inital SpecialS   //
////////////////////////


void SpecialS(GOBJ *gobj)
{
	// get fighter data
	FighterData *fighter_data = gobj->userdata;

	// get special attributes pointer
	ToadAttr *tdAttr = fighter_data->special_attributes;

	// clear flag
	fighter_data->ftcmd_var.flag2 = 0;

	// change to special S state and update
	ActionStateChange(0, 1, 0, gobj, STATE_SPECIALSAIR, 0, 0);
	Fighter_AdvanceScript(gobj);

	// set initial Y velocity and clamp X velocity
	fighter_data->phys.self_vel.Y = 0.6 - tdAttr->specialS_rising_tap_power;
	Fighter_ClampHorizontalVelocity(fighter_data, tdAttr->specialS_base_air_speed);

	// clear flags for this state
	SpecialSFtCmd *script_flags = &fighter_data->ftcmd_var;
	script_flags->decay_air_speed = 0;
	script_flags->disable_rise = 0;

	// clear state variables
	SpecialSVar *state_var = &fighter_data->state_var;
	state_var->air_speed = 0;
	state_var->on_ground = 0;

	// note: this variable is set but unused? (wierd haha)
	state_var->x04 = 4 + 1;

	// set take damage and death callbacks
	// these reset some kind of bone rotation yaw
	fighter_data->cb.OnTakeDamage = 0x800e2050;
	fighter_data->cb.OnDeath_State = 0x800e2050;

	// spawn effect
	Effect_SpawnSync(MEX_EFFECT_DSPECIAL, gobj, gobj->hsd_object);

	// enable gfx bit flag
	fighter_data->flags.persistent_gfx = 1;

	// set endlag callbacks to pause and resume
	fighter_data->cb.EnterHitlag = Effect_PauseAll;
	fighter_data->cb.ExitHitlag = Effect_ResumeAll;
	return;
}

void SpecialAirS(GOBJ *gobj)
{
	// get fighter data
	FighterData *fighter_data = gobj->userdata;

	// get special attributes pointer
	ToadAttr *tdAttr = fighter_data->special_attributes;

	// clear flag
	fighter_data->ftcmd_var.flag2 = 0;

	// change to special S state and update
	ActionStateChange(0, 1, 0, gobj, STATE_SPECIALSAIR, 0, 0);
	Fighter_AdvanceScript(gobj);

	// set initial Y velocity and clamp X velocity
	float y_vel = 0;

	// if this variable is set then set y vel reduction to initial rising power
	if (fighter_data->fighter_var.ft_var3 == 0)
		y_vel = tdAttr->specialS_rising_tap_power;

	fighter_data->phys.self_vel.Y = 0.6 - y_vel;

	// clamp vertical velocity
	Fighter_ClampHorizontalVelocity(fighter_data, tdAttr->specialS_base_air_speed);

	// clear flags
	SpecialSFtCmd *script_flags = &fighter_data->ftcmd_var;
	script_flags->decay_air_speed = 0;
	script_flags->disable_rise = 0;

	// clear state variables
	SpecialSVar *state_var = &fighter_data->state_var;
	state_var->air_speed = 0;
	state_var->on_ground = 0;

	// note: this variable is set but unused?
	state_var->x04 = 4 + 1;

	// set take damage and death callbacks
	// these reset some kind of bone rotation yaw
	fighter_data->cb.OnTakeDamage = 0x800e2050;
	fighter_data->cb.OnDeath_State = 0x800e2050;

	// spawn effect
	Effect_SpawnSync(MEX_EFFECT_DSPECIAL, gobj, gobj->hsd_object);

	// enable gfx bit flag
	fighter_data->flags.persistent_gfx = 1;

	// set endlag callbacks to pause and resume
	fighter_data->cb.EnterHitlag = Effect_PauseAll;
	fighter_data->cb.ExitHitlag = Effect_ResumeAll;
	return;
}

////////////////////////
// Grounded SpecialS  //
////////////////////////

void SpecialS_AnimationCallback(GOBJ *gobj)
{
	FighterData *fighter_data = gobj->userdata;

	if (FrameTimerCheck(gobj) == 0)
	{
		fighter_data->cb.OnTakeDamage = (void *)0x0;
		fighter_data->cb.OnDeath_State = (void *)0x0;
		Fighter_EnterWait(gobj);
	}
	return;
}
///
/// 0x800E23DC
///
void SpecialS_IASACallback(GOBJ *gobj)
{
	return;
}
///
/// 0x800E23E4
///
void SpecialS_PhysicCallback(GOBJ *gobj)
{
	FighterData *fighter_data = gobj->userdata;
	ToadAttr *tdAttr = fighter_data->special_attributes;
	SpecialSFtCmd *script_flags = &fighter_data->ftcmd_var;

	float base_air_speed = tdAttr->specialS_base_air_speed;
	float airSpeed = base_air_speed;

	SpecialSVar *state_var = &fighter_data->state_var;

	if (script_flags->decay_air_speed != 0)
	{
		float new_air_speed = state_var->air_speed - 0.83;

		state_var->air_speed = new_air_speed;

		airSpeed = base_air_speed + new_air_speed;

		if (airSpeed < 0)
			airSpeed = 0;
	}

	Fighter_QueueAllowXDrift(fighter_data, 0, tdAttr->specialS_x_accel, airSpeed);

	Fighter_PhysGround_ApplyVelocity(gobj);

	if ((fighter_data->ftcmd_var.flag2 != 0)  != 0)
	{
		fighter_data->phys.self_vel.Y = fighter_data->phys.self_vel.Y + tdAttr->specialS_rising_tap_power;

		fighter_data->ftcmd_var.flag2 = 0;

		Fighter_SetAirborne(fighter_data);

		ActionStateChange(fighter_data->state.frame, 1, 0, gobj, STATE_SPECIALSAIR, 0xc4c508a, 0);

		Fighter_ClampFallSpeed(fighter_data, tdAttr->specialS_terminal_velocity);

		Fighter_ClampHorizontalVelocity(fighter_data, tdAttr->specialS_x_vel_clamp);

		fighter_data->cb.EnterHitlag = Effect_PauseAll;
		fighter_data->cb.ExitHitlag = Effect_ResumeAll;
	}
	return;
}
///
/// 0x80082888
///
int SpecialS_UpdateECBBox(GOBJ *gobj, ECBSize *ecb_bones)
{
	FighterData *fighter_data = (FighterData *)gobj->userdata;

	fighter_data->coll_data.topN_Prev.X = fighter_data->coll_data.topN_Curr.X;
	fighter_data->coll_data.topN_Prev.Y = fighter_data->coll_data.topN_Curr.Y;
	fighter_data->coll_data.topN_Prev.Z = fighter_data->coll_data.topN_Curr.Z;

	fighter_data->coll_data.topN_Curr.X = fighter_data->phys.pos.X;
	fighter_data->coll_data.topN_Curr.Y = fighter_data->phys.pos.Y;
	fighter_data->coll_data.topN_Curr.Z = fighter_data->phys.pos.Z;

	if (fighter_data->facing_direction < 0)
	{
		ecb_bones->right.X = -ecb_bones->right.X;
		ecb_bones->left.X = -ecb_bones->left.X;
	}

	int is_touching_ground = ECB_CollGround_PassLedge(&fighter_data->coll_data, ecb_bones);

	fighter_data->phys.pos.X = fighter_data->coll_data.topN_Curr.X;
	fighter_data->phys.pos.Y = fighter_data->coll_data.topN_Curr.Y;
	fighter_data->phys.pos.Z = fighter_data->coll_data.topN_Curr.Z;

	return is_touching_ground;
}
///
/// 0x800E25C4
///
void SpecialS_CollisionCallback(GOBJ *gobj)
{
	FighterData *fighter_data = gobj->userdata;
	ToadAttr *tdAttr = fighter_data->special_attributes;
	SpecialSVar *state_var = &fighter_data->state_var;

	ECBSize fake_ecb = {12, 0, -6, 6, 6, 6};

	if (fighter_data->phys.air_state == 0)
	{
		if (SpecialS_UpdateECBBox(gobj, &fake_ecb) == 0)
		{
			fighter_data->ftcmd_var.flag2 = 0;
			Fighter_SetAirborne(fighter_data);
			ActionStateChange(fighter_data->state.frame, 1, 0, gobj, STATE_SPECIALSAIR, 0xc4c508a, 0);
			Fighter_ClampFallSpeed(fighter_data, tdAttr->specialS_terminal_velocity);
			Fighter_ClampHorizontalVelocity(fighter_data, tdAttr->specialS_x_vel_clamp);
			fighter_data->cb.EnterHitlag = Effect_PauseAll;
			fighter_data->cb.ExitHitlag = Effect_ResumeAll;
			state_var->on_ground = 0;
		}
		else
		{
			state_var->on_ground = 1;
		}
	}
	else
	{
		if (Fighter_CollAir_DefineECB(gobj, &fake_ecb) == 0)
		{
			fighter_data->ftcmd_var.flag2 = 0;
			Fighter_SetAirborne(fighter_data);
			ActionStateChange(fighter_data->state.frame, 1, 0, gobj, STATE_SPECIALSAIR, 0xc4c508a, 0);
			Fighter_ClampFallSpeed(fighter_data, tdAttr->specialS_terminal_velocity);
			Fighter_ClampHorizontalVelocity(fighter_data, tdAttr->specialS_x_vel_clamp);
			fighter_data->cb.EnterHitlag = Effect_PauseAll;
			fighter_data->cb.ExitHitlag = Effect_ResumeAll;
			state_var->on_ground = 0;
		}
		else
		{
			state_var->on_ground = 1;
		}
	}

	if ((fighter_data->ftcmd_var.flag3 == 0) || (state_var->on_ground == 0))
	{
		// Reset Rotation if not grounded
		Fighter_SetBoneRotZ(fighter_data, 0, 0);
	}
	else
	{
		// Rotate to ground slope angle
		float angle = atan2(fighter_data->coll_data.ground_slope.X, fighter_data->coll_data.ground_slope.Y);
		Fighter_SetBoneRotZ(fighter_data, 0, -1 * angle);
	}
	return;
}
////////////////////////
//  Aerial SpecialS   //
////////////////////////
///
/// 0x800E2308
///
void SpecialAirS_AnimationCallback(GOBJ *gobj)
{
	FighterData *fighter_data = gobj->userdata;
	ToadAttr *tdAttr = fighter_data->special_attributes;
	SpecialSFtCmd *script_flags = &fighter_data->ftcmd_var;

	if (script_flags->disable_rise != 0)
	{
		script_flags->disable_rise = 0;
		fighter_data->fighter_var.ft_var3 = 1;
	}

	if (FrameTimerCheck(gobj) == 0)
	{
		fighter_data->cb.OnTakeDamage = (void *)0x0;
		fighter_data->cb.OnDeath_State = (void *)0x0;

		if (true)
		{
			Fighter_EnterFall(gobj);
		}
		else
		{
			Fighter_EnterSpecialFall(gobj, 1, 0, 1, 1, 0);
		}
	}
	return;
}
///
/// 0x800E23E0
///
void SpecialAirS_IASACallback(GOBJ *gobj)
{
	return;
}
///
/// 0x800E2508
///
void SpecialAirS_PhysicCallback(GOBJ *gobj)
{
	FighterData *fighter_data = gobj->userdata;
	ToadAttr *tdAttr = fighter_data->special_attributes;
	SpecialSVar *state_var = &fighter_data->state_var;
	SpecialSFtCmd *script_flags = &fighter_data->ftcmd_var;

	if (fighter_data->fighter_var.ft_var3 == 0)
	{
		if ((fighter_data->ftcmd_var.flag2 != 0)  != 0)
		{
			Fighter_AddClampYPosition(fighter_data, tdAttr->specialS_rising_tap_power, tdAttr->specialS_terminal_velocity);
		}
	}

	Fighter_Phys_ApplyVerticalAirFriction(fighter_data);

	float base_air_speed = tdAttr->specialS_base_air_speed;
	float airSpeed = base_air_speed;

	if (script_flags->decay_air_speed != 0)
	{
		float new_air_speed = state_var->air_speed - 0.83;

		state_var->air_speed = new_air_speed;

		airSpeed = base_air_speed + new_air_speed;

		if (airSpeed < 0)
			airSpeed = 0;
	}

	Fighter_AllowXDrift(fighter_data, 0, tdAttr->specialS_x_drift, airSpeed);
	return;
}
///
/// 0x800E2778
///
void SpecialAirS_CollisionCallback(GOBJ *gobj)
{
	FighterData *fighter_data = gobj->userdata;
	ToadAttr *tdAttr = fighter_data->special_attributes;
	SpecialSVar *state_var = &fighter_data->state_var;

	ECBSize fake_ecb = {12, 0, -6, 6, 6, 6};

	if (Fighter_CollAir_DefineECB(gobj, &fake_ecb) == 0)
	{
		state_var->on_ground = 0;
	}
	else
	{
		fighter_data->ftcmd_var.flag2 = 0;

		Fighter_SetGrounded2(fighter_data);

		fighter_data->phys.self_vel.Y = 0;
		fighter_data->fighter_var.ft_var3 = 0;

		ActionStateChange(fighter_data->state.frame, 1, 0, gobj, STATE_SPECIALS, 0xc4c508a, 0);

		Fighter_ClampHorizontalGroundVelocity(fighter_data, tdAttr->specialS_base_air_speed);

		fighter_data->cb.EnterHitlag = Effect_PauseAll;
		fighter_data->cb.ExitHitlag = Effect_ResumeAll;
		state_var->on_ground = 1;
	}

	// set rotation
	if ((fighter_data->ftcmd_var.flag3 == 0) || (state_var->on_ground == 0))
	{
		// if in air reset rotation
		Fighter_SetBoneRotZ(fighter_data, 0, 0);
	}
	else
	{
		// if on ground rotate to ground slope
		float angle = atan2(fighter_data->coll_data.ground_slope.X, fighter_data->coll_data.ground_slope.Y);
		Fighter_SetBoneRotZ(fighter_data, 0, -1 * angle);
	}
	return;
}