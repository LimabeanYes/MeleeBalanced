#include "toad.h"

///////////////////////
//  Enter SpecialLw  //
///////////////////////

void SpecialLw(GOBJ* fighter)
{
	FighterData* fighter_data = fighter->userdata;

	fighter_data->ftcmd_var.flag0 = 0;
	fighter_data->ftcmd_var.flag1 = 0;
	fighter_data->ftcmd_var.flag2 = 0;
	fighter_data->ftcmd_var.flag3 = 0;

	ActionStateChange(0, 1, 0, fighter, STATE_SPECIALLW, 0, 0);
	Fighter_AdvanceScript(fighter);

	return;
}

void SpecialAirLw(GOBJ* fighter)
{
	FighterData* fighter_data = fighter->userdata;

	fighter_data->ftcmd_var.flag0 = 0;
	fighter_data->ftcmd_var.flag1 = 0;
	fighter_data->ftcmd_var.flag2 = 0;
	fighter_data->ftcmd_var.flag3 = 0;

	ActionStateChange(0, 1, 0, fighter, STATE_SPECIALLWAIR, 0, 0);
	Fighter_AdvanceScript(fighter);

	return;
}

//////////////////////
//       Misc       //
//////////////////////


///////////////////////
//  Ground SpecialLw //
///////////////////////


void SpecialLw_AnimationCallback(GOBJ* gobj)
{
	FighterData* fd = gobj->userdata;
	ToadCharVar* charvar = &fd->fighter_var;

	if (fd->ftcmd_var.flag1 != 0) {				//check if script flag 1 is set
		fd->ftcmd_var.flag1 = 0;				//set it back to 0 so that it isnt reran
		charvar->stance = charvar->stance + 1;	//Up the stance by 1
		if (charvar->stance >= STANCE_MAX) {	//check to see if the maximum stance has been reached
			charvar->stance = STANCE_MAX;				//if it has, go back to the original stance
		}
		charvar->stance_framesRemaining = 1200;
	}

	if (FrameTimerCheck(gobj) == 0)
	{
		Fighter_EnterWait(gobj);
	}

	return;
}

void SpecialLw_IASACallback(GOBJ* gobj)
{
	return;
}

void SpecialLw_PhysicCallback(GOBJ* gobj)
{
	Fighter_PhysGround_ApplyFriction(gobj);
	return;
}

void SpecialLw_CollisionCallback(GOBJ* gobj)
{
	if (Fighter_CollGround_StopLedge(gobj) != 1)
	{
		Fighter_EnterFall(gobj);
	}

	return;
}

///////////////////////
//  Aerial SpecialN  //
///////////////////////

void SpecialAirLw_AnimationCallback(GOBJ* gobj)
{
	if (FrameTimerCheck(gobj) == 0)
	{
		Fighter_EnterFall(gobj);
	}

	return;
}

void SpecialAirLw_IASACallback(GOBJ* gobj)
{
	return;
}

void SpecialAirLw_PhysicCallback(GOBJ* gobj)
{
	Fighter_PhysAir_ApplyGravityFastfall(gobj);
	return;
}

void SpecialAirLw_EnterGrounded(GOBJ* gobj)
{
	FighterData* fighter_data = (FighterData*)gobj->userdata;
	Fighter_SetGrounded2(fighter_data);
	ActionStateChange(fighter_data->state.frame, 1, 0, gobj, STATE_SPECIALLW, 0x5000, 0);
	return;
}

void SpecialAirLw_CollisionCallback(GOBJ* gobj)
{
	if (Fighter_CollAir_IgnoreLedge_NoCB(gobj) != 0)
	{
		Fighter_EnterSpecialLanding(gobj, 0, 8);
	}

	return;
}