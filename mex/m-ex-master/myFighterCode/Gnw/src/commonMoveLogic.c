#include "gnw.h"

static void* originalGrab_phys_callback;
#define GET_STORED_SPEED_VAR float* storedSpeed = &fd->fighter_var.ft_var52
#define storedSpeed *storedSpeed

void ThrowB_PhysCallback(GOBJ* gobj) {
	if(origina rab_anim_callback!=0) ((void(*)(GOBJ*))originalGrab_phys_callback)(gobj);
	FighterData* fd = gobj->userdata;
	GET_STORED_SPEED_VAR;
	if (storedSpeed != 0) {
		Fighter_SetAirborne(fd);
		fd->phys.self_vel.Y = storedSpeed;
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
		originalGrab_phys_callback = fp->ftstates_common[ASID_THROWB].physics_callback;
		fp->ftstates_common[ASID_THROWB].physics_callback = ThrowB_PhysCallback;
	}
}

void OnLoad(GOBJ* fighter_gobj)
{
	FighterData* fighter_data = fighter_gobj->userdata;

	SetCommonMoveLogic(fighter_data);

	void (*cb_OnLoad)(GOBJ * gobj) = (void*)0x8014A37C; // Vanilla Roy OnLoad callback
	cb_OnLoad(fighter_gobj);
}

void OnDestroy(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	OSReport("onDestroy\n");
	if (fd->ftstates_common != 0x803c2800) {
		HSD_Free(fd->ftstates_common);
	}
}