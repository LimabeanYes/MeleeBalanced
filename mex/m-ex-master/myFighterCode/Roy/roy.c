#include "roy.h"

static void* originalLw3_iasa_callback;
static void* originalLw3_anim_callback;
#define GET_FLAG_VAR int* flagVar = &fd->fighter_var.ft_var52

enum tiltDirection {
	TILT_NONE,
	TILT_UP,
	TILT_DOWN,
	TILT_LEFT,
	TILT_RIGHT
};

void giveDamage_lw3(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	GET_FLAG_VAR;
	*flagVar = 1;
}

int decide_tiltDir(Vec2 stickPos) {
	if (stickPos.Y > 0.3) {
		return TILT_UP;
	}
	else if (stickPos.Y < -0.3) {
		return TILT_DOWN;
	}
	else {
		return TILT_NONE;
	}
}

void tilt_iasa(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	GET_FLAG_VAR;
	Vec2 stickPos = fd->input.lstick;
	
	int tiltDir = decide_tiltDir(stickPos);

	if (*flagVar == 1 &&
		((fd->input.down & HSD_BUTTON_A) != 0 || (fd->input.down & HSD_TRIGGER_Z) != 0)) {
		int state;

		switch (tiltDir)
		{
		case TILT_UP:
			state = ASID_ATTACKHI3;
			break;
		case TILT_DOWN:
			state = ASID_ATTACKLW3;
			break;
		default:
			return;
			break;
		}

		*flagVar = 0;
		fd->cb.OnGiveDamage = 0;
		OSReport("Switching to ATTACKHI3\n");
		ActionStateChange(0, 1, 0, gobj, state, 0x0, 0);
	}
}

void AttackLw3_AnimCallback(GOBJ* gobj) {
	if (originalLw3_anim_callback != 0) {
		((void(*)(GOBJ*))originalLw3_anim_callback)(gobj);
	}
	FighterData* fd = gobj->userdata;
	GET_FLAG_VAR;
	if (fd->state.frame <= 2) {
		*flagVar = 0;
		fd->cb.OnGiveDamage = giveDamage_lw3;
	}
}

void AttackLw3_IASAcallback(GOBJ* gobj) {
	if (originalLw3_iasa_callback != 0) {
		((void(*)(GOBJ*))originalLw3_iasa_callback)(gobj);
	}
	FighterData* fd = gobj->userdata;
	GET_FLAG_VAR;
	float stickPos = fd->input.lstick.Y;
	tilt_iasa(gobj);
	return;
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
		originalLw3_anim_callback = fp->ftstates_common[ASID_ATTACKLW3].animation_callback;
		originalLw3_iasa_callback = fp->ftstates_common[ASID_ATTACKLW3].iasa_callback;
		fp->ftstates_common[ASID_ATTACKLW3].iasa_callback = AttackLw3_IASAcallback;
		fp->ftstates_common[ASID_ATTACKLW3].animation_callback = AttackLw3_AnimCallback;
	}
}

void OnLoad(GOBJ* fighter_gobj)
{
	FighterData* fighter_data = fighter_gobj->userdata;

	SetCommonMoveLogic(fighter_data);

	void (*cb_OnLoad)(GOBJ * gobj) = (void*)0x8014F124; // Vanilla Roy OnLoad callback
	cb_OnLoad(fighter_gobj);
}

void OnDestroy(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	OSReport("onDestroy\n");
	if (fd->ftstates_common != 0x803c2800) {
		HSD_Free(fd->ftstates_common);
	}
}