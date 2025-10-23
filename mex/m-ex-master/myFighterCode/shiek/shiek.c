#include "mex.h"

static void* originaldair_phys;
#define DAIR_JUMPVEL 3.0f

void giveDamage_dair(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	if (fd->input.held & HSD_BUTTON_A || fd->input.cstick.Y < -0.33 || fd->input.held & HSD_TRIGGER_Z) {
		fd->phys.self_vel.Y = DAIR_JUMPVEL;
		fd->jump.jumps_used = 0;
		ActionStateChange(0, 1, 0, gobj, ASID_JUMPB, 0x0, 0);
	}
}
void Dair_phys(GOBJ* gobj) {
	if (originaldair_phys != 0) {
		((void(*)(GOBJ*))originaldair_phys)(gobj);
	}
	FighterData* fd = gobj->userdata;
	fd->cb.OnGiveDamage = giveDamage_dair;
	fd->cb.ExitHitlag = giveDamage_dair;
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
		originaldair_phys = fp->ftstates_common[ASID_ATTACKAIRLW].physics_callback;
		fp->ftstates_common[ASID_ATTACKAIRLW].physics_callback = Dair_phys;
	}
	OSReport("SetCommonMoveLogic complete\n");
}

void OnLoad(GOBJ* fighter_gobj)
{
	FighterData* fighter_data = fighter_gobj->userdata;

	SetCommonMoveLogic(fighter_data);

	void (*cb_OnLoad)(GOBJ * gobj) = (void*)0x801100EC; // Vanilla Roy OnLoad callback
	cb_OnLoad(fighter_gobj);
}

void OnDestroy(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	OSReport("onDestroy\n");
	if (fd->ftstates_common != 0x803c2800) {
		HSD_Free(fd->ftstates_common);
	}
}


/*
FtState move_logic[] = {
	[0] = {
		.action_id = 295,
		.flags = 0x00340111,
		.move_id = ATKKIND_SPECIALN,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80112248,
		.iasa_callback = 0x801126C8,
		.physics_callback = 0x80112878,
		.collision_callback = 0x80112978,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[1] = {
		.action_id = 296,
		.flags = 0x003C0111,
		.move_id = ATKKIND_SPECIALN,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x801122D8,
		.iasa_callback = 0x801126CC,
		.physics_callback = 0x80112898,
		.collision_callback = 0x801129F8,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[2] = {
		.action_id = 297,
		.flags = 0x00340111,
		.move_id = ATKKIND_SPECIALN,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80112384,
		.iasa_callback = 0x80112798,
		.physics_callback = 0x801128B8,
		.collision_callback = 0x80112A78,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[3] = {
		.action_id = 298,
		.flags = 0x00340111,
		.move_id = ATKKIND_SPECIALN,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x801123CC,
		.iasa_callback = 0x8011279C,
		.physics_callback = 0x801128D8,
		.collision_callback = 0x80112B00,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[4] = {
		.action_id = 299,
		.flags = 0x00340511,
		.move_id = ATKKIND_SPECIALN,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80112450,
		.iasa_callback = 0x801127A0,
		.physics_callback = 0x801128F8,
		.collision_callback = 0x80112B98,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[5] = {
		.action_id = 300,
		.flags = 0x003C0511,
		.move_id = ATKKIND_SPECIALN,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x801124E0,
		.iasa_callback = 0x801127A4,
		.physics_callback = 0x80112918,
		.collision_callback = 0x80112C18,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[6] = {
		.action_id = 301,
		.flags = 0x00340511,
		.move_id = ATKKIND_SPECIALN,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x8011258C,
		.iasa_callback = 0x80112870,
		.physics_callback = 0x80112938,
		.collision_callback = 0x80112C98,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[7] = {
		.action_id = 302,
		.flags = 0x00340511,
		.move_id = ATKKIND_SPECIALN,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x8011260C,
		.iasa_callback = 0x80112874,
		.physics_callback = 0x80112958,
		.collision_callback = 0x80112CE4,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[8] = {
		.action_id = 303,
		.flags = 0x00340012,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x801112CC,
		.iasa_callback = 0x80111344,
		.physics_callback = 0x8011134C,
		.collision_callback = 0x801113C8,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[9] = {
		.action_id = 305,
		.flags = 0x003C0012,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80111588,
		.iasa_callback = 0x80111708,
		.physics_callback = 0x80111778,
		.collision_callback = 0x801117B8,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[10] = {
		.action_id = 304,
		.flags = 0x00340012,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80111A48,
		.iasa_callback = 0x80111BF0,
		.physics_callback = 0x80111BF8,
		.collision_callback = 0x80111C38,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[11] = {
		.action_id = 306,
		.flags = 0x00340412,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80111308,
		.iasa_callback = 0x80111348,
		.physics_callback = 0x8011136C,
		.collision_callback = 0x80111404,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[12] = {
		.action_id = 308,
		.flags = 0x003C0412,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80111648,
		.iasa_callback = 0x80111740,
		.physics_callback = 0x80111798,
		.collision_callback = 0x801117F4,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[13] = {
		.action_id = 307,
		.flags = 0x00340412,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80111B1C,
		.iasa_callback = 0x80111BF4,
		.physics_callback = 0x80111C18,
		.collision_callback = 0x80111C74,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[14] = {
		.action_id = 309,
		.flags = 0x00340213,
		.move_id = ATKKIND_SPECIALHI,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80113194,
		.iasa_callback = 0x8011320C,
		.physics_callback = 0x80113214,
		.collision_callback = 0x80113278,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[15] = {
		.action_id = 309,
		.flags = 0x00340213,
		.move_id = ATKKIND_SPECIALHI,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x801133FC,
		.iasa_callback = 0x80113474,
		.physics_callback = 0x8011347C,
		.collision_callback = 0x801134A0,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[16] = {
		.action_id = 310,
		.flags = 0x00340213,
		.move_id = ATKKIND_SPECIALHI,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80113C40,
		.iasa_callback = 0x80113CDC,
		.physics_callback = 0x80113CE4,
		.collision_callback = 0x80113D80,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[17] = {
		.action_id = 311,
		.flags = 0x00340613,
		.move_id = ATKKIND_SPECIALHI,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x801131D0,
		.iasa_callback = 0x80113210,
		.physics_callback = 0x80113234,
		.collision_callback = 0x801132B4,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[18] = {
		.action_id = 311,
		.flags = 0x00340613,
		.move_id = ATKKIND_SPECIALHI,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80113438,
		.iasa_callback = 0x80113478,
		.physics_callback = 0x8011349C,
		.collision_callback = 0x80113540,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[19] = {
		.action_id = 312,
		.flags = 0x00340613,
		.move_id = ATKKIND_SPECIALHI,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80113C7C,
		.iasa_callback = 0x80113CE0,
		.physics_callback = 0x80113D04,
		.collision_callback = 0x80113DBC,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[20] = {
		.action_id = 313,
		.flags = 0x00340014,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x801142E8,
		.iasa_callback = 0x80114368,
		.physics_callback = 0x80114370,
		.collision_callback = 0x801143D4,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[21] = {
		.action_id = 314,
		.flags = 0x00340014,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80114524,
		.iasa_callback = 0x8011459C,
		.physics_callback = 0x801145A4,
		.collision_callback = 0x80114608,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[22] = {
		.action_id = 315,
		.flags = 0x00340414,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80114328,
		.iasa_callback = 0x8011436C,
		.physics_callback = 0x80114390,
		.collision_callback = 0x80114410,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[23] = {
		.action_id = 316,
		.flags = 0x00340414,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80114560,
		.iasa_callback = 0x801145A0,
		.physics_callback = 0x801145C4,
		.collision_callback = 0x80114644,
		.camera_callback = Fighter_UpdateCameraBox,
	},
};
*/