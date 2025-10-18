#include "bowser.h"

void AttackLw3_IASAcallback(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	Lw3Var* state_var = Fighter_GetStateVars(gobj);

	if (fd->ftcmd_var.flag3 == 1) { //if flag 3 (subaction) is 1 (for buffering)
		if ((fd->input.down & HSD_BUTTON_A) != 0) {
			state_var->a_hasBeenPressed = 1; //confirms that A has been pressed
		}
	}

	if (fd->ftcmd_var.flag2 == 1 && state_var->a_hasBeenPressed == 0) { //flag 2 is 1 & move not buffered 
		Fighter_EnterSpecialLanding(gobj, 0, 5); //dont run the 2nd hit
		//ActionStateChange(45, 1, 0.5, gobj, ASID_ATTACKLW3, 0, 0);
	}
	else if (FrameTimerCheck(gobj) == 0) {
		Fighter_EnterWait(gobj); //run second hit
	}
	return;
}

void AttackS4_Animationcallback(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	fd->dmg.armor = ARMOUR_CONST;
	if (FrameTimerCheck(gobj) == 0) {
		fd->dmg.armor = 0;
		Fighter_EnterWait(gobj);
	}
}

void AttackHi4_Animationcallback(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	fd->dmg.armor = ARMOUR_CONST;
	if (FrameTimerCheck(gobj) == 0) {
		fd->dmg.armor = 0;
		Fighter_EnterWait(gobj);
	}
}

void AttackAirHi_Animationcallback(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	fd->dmg.armor = ARMOUR_CONST;
	if (FrameTimerCheck(gobj) == 0) {
		fd->dmg.armor = 0;
		Fighter_EnterFall(gobj);
	}
}

void SetCommonMoveLogic(FighterData* fp)
{
	if (fp->ftstates_common == 0x803c2800)
	{
		// create a copy of common move logic
		uint state_size = sizeof(FtState) * fp->common_state_num;
		FtState* common_logic_copy = HSD_MemAlloc(state_size);
		memcpy(common_logic_copy, fp->ftstates_common, state_size);
		fp->ftstates_common = common_logic_copy;

		// change common states
		fp->ftstates_common[ASID_ATTACKLW3].iasa_callback = AttackLw3_IASAcallback;
		fp->ftstates_common[ASID_ATTACKAIRHI].animation_callback = AttackAirHi_Animationcallback;
		fp->ftstates_common[ASID_ATTACKS4S].animation_callback = AttackS4_Animationcallback;
		fp->ftstates_common[ASID_ATTACKHI4].animation_callback = AttackHi4_Animationcallback;
	}
}

void OnLoad(GOBJ* fighter_gobj)
{
	FighterData* fighter_data = fighter_gobj->userdata;

	SetCommonMoveLogic(fighter_data);

	void (*cb_OnLoad)(GOBJ * gobj) = (void*)0x80132ABC; // Vanilla Bowser OnLoad callback
	cb_OnLoad(fighter_gobj);
}

void OnDestroy(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	if (fd->ftstates_common != 0x803c2800) {
		HSD_Free(fd->ftstates_common);
	}
}