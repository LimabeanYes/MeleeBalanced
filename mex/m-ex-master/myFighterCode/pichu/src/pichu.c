#include "pichu.h"

static float ogWeight;

void meterLogic(GOBJ* gobj)
{
	JOBJ* jobjay = gobj->hsd_object;
	JOBJ* jobj_CurrCharge; //Number group JOBJ
	JOBJ_GetChild(jobjay, &jobj_CurrCharge, 0, -1); //joint 0, meter and chicanery

	MeterVars* meterData = gobj->userdata;
	RelaxOnfame(meterData->fighter, gobj);

	if (meterData->fighter != 0 && (Pause_CheckStatus(1) != 2) && (Fighter_GetStocks(meterData->ply) > 0))
	{
		FighterData* fighterData = meterData->fighter->userdata;
		ftPichu_FighterVars* charvar = &fighterData->fighter_var;

		jobjay->trans = *Match_GetPlayerHUDPos(fighterData->ply);
		jobjay->trans.X = jobjay->trans.X - 4.6; //-5.04;
		jobjay->trans.Y = jobjay->trans.Y + 2.375;

		int frameCalc = charvar->framecounter / 15;

		DOBJ* myDobj = JOBJ_GetDObj(jobj_CurrCharge);
		MOBJ* myMobj = myDobj->mobj;
		HSD_Material* myMaterial = myMobj->mat;

		GXColor meterColour;
		if (charvar->flag_meterMode != 0) {
			meterColour.r = 255;
			meterColour.g = 255;
			meterColour.b = 0 + HSD_Randi(2);
			meterColour.a = 175;
		}
		else {
			meterColour.r = 60 + HSD_Randi(5);
			meterColour.g = 60 + HSD_Randi(5);
			meterColour.b = 60 + HSD_Randi(5);
			meterColour.a = 175;
		}
		myMaterial->diffuse = meterColour;
		myMaterial->specular = meterColour;
		myMaterial->ambient = meterColour;

		if (!(JOBJ_GetAnimFrame(jobj_CurrCharge) == frameCalc))
		{

			if (JOBJ_GetAnimFrame(jobj_CurrCharge) < frameCalc)
			{
				JOBJ_ReqAnimAll(jobj_CurrCharge, frameCalc);
			}
			if (JOBJ_GetAnimFrame(jobj_CurrCharge) > frameCalc)
			{
				JOBJ_ReqAnimAll(jobj_CurrCharge, JOBJ_GetAnimFrame(jobj_CurrCharge) - 1);
			}
			//JOBJ_RunAObjCallback(jobj_CurrCharge, 6, 0x20, AOBJ_StopAnim, 6, 0, 0);
			JOBJ_AnimAll(jobj_CurrCharge);
		}
		JOBJ_ClearFlagsAll(jobjay, JOBJ_HIDDEN);
		JOBJ_SetMtxDirtySub(jobjay);
	}
	else
	{
		JOBJ_SetFlagsAll(jobjay, JOBJ_HIDDEN);
	}
}

//setup meter gobj
GOBJ* setupMeter(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;

	//load meter file
	HSD_Archive* meterArchive = Archive_LoadFile(METER_FILENAME);

	//load symbol, setup jobj
	Symbol_WpInd_scene_models* meterModel = Archive_GetPublicAddress(meterArchive, METER_SYMBOL);

	JOBJSet* jobjset_WpInd = meterModel->WpInd_scene_models;

	//gobj setup
	GOBJ* gobj_WpInd = JOBJ_LoadSet(0, jobjset_WpInd, 0, 0, 0, 11, 1, meterLogic);
	void* UserData = calloc(sizeof(MeterVars));
	GObj_AddUserData(gobj_WpInd, 4, HSD_Free, UserData);

	//var setup
	MeterVars* meterData = gobj_WpInd->userdata;
	meterData->fighter = gobj;
	meterData->ply = fd->ply;
	return gobj_WpInd;
}

void RelaxOnfame(GOBJ* fighter_gobj, GOBJ* tension_gobj)
{
	//get fighter data
	FighterData* fighterData = fighter_gobj->userdata;
	ftPichu_FighterVars* charvar = &fighterData->fighter_var;

	//get meter data
	MeterVars* meterData = tension_gobj->userdata;
	
	//meter mode reset
	if (charvar->framecounter < 0) {
		charvar->framecounter = 0;
		charvar->flag_meterMode = 0;
	}

	

}

void onFrame(GOBJ* gobj) {
	FighterData* fighterData = gobj->userdata;
	ftPichu_FighterVars* charvar = &fighterData->fighter_var;
	if (charvar->flag_meterMode != 0) {
		fighterData->attr.weight = ogWeight * 1.25;
	}
	else {
		fighterData->attr.weight = ogWeight;
	}
	//meter behaviour
	if (Pause_CheckStatus(1) != 2) {
		if (charvar->flag_meterMode == 0) {
			charvar->framecounter++;
			//OSReport("Framecount: %d\n", charvar->framecounter);
		}
		else {
			charvar->framecounter -= 1.5;
		}
		if (charvar->framecounter >= FRAMES_UNTIL_METERFULL) {
			charvar->flag_meterMode = 1;
		}
	}
}

void onLoad(GOBJ* gobj) {
	void (*onload)(GOBJ * gobj) = (void*)0x80149E34;
	onload(gobj);

	FighterData* fd = gobj->userdata;
	ftPichu_FighterVars* pcvar = &fd->fighter_var;
	setupMeter(gobj);
}
void onSpawn(GOBJ* gobj) {
	void (*onspawn)(GOBJ * gobj) = (void*)0x80149EAC;
	onspawn(gobj);
	FighterData* fd = gobj->userdata;
	ftPichu_FighterVars* pcvar = &fd->fighter_var;
	pcvar->flag_meterMode = 0;
	pcvar->framecounter = 0;
}
void onRespawn(GOBJ* gobj) {
	void (*onspawn)(GOBJ * gobj) = (void*)0x80149EAC;
	onspawn(gobj);
	FighterData* fd = gobj->userdata;
	ftPichu_FighterVars* pcvar = &fd->fighter_var;
	pcvar->flag_meterMode = 0;
	pcvar->framecounter = 0;
}

void specialLw(GOBJ* gobj) {
	void (*ogSpecialLw)(GOBJ* gobj) = (void*)0x801278BC;
	FighterData* fd = gobj->userdata;
	ftPichu_FighterVars* pcvar = &fd->fighter_var;
	if (pcvar->flag_meterMode == 1) {
		ActionStateChange(0, 1, 0, gobj, asid_SpecialLwAlt, 0x0, 0);
		Fighter_AdvanceScript(gobj);
	}
	else {
		ogSpecialLw(gobj);
	}
	return;
}

void specialAirLw(GOBJ* gobj) {
	void (*ogSpeciaAirlLw)(GOBJ * gobj) = (void*)0x80127924;
	FighterData* fd = gobj->userdata;
	ftPichu_FighterVars* pcvar = &fd->fighter_var;
	if (pcvar->flag_meterMode == 1) {
		ActionStateChange(0, 1, 0, gobj, asid_SpecialAirLwAlt, 0x0, 0);
		Fighter_AdvanceScript(gobj);
	}
	else {
		ogSpeciaAirlLw(gobj);
	}
	return;
}

void specialLwAlt_groundToAir(GOBJ* gobj) {
	FighterData* fighter_data = (FighterData*)gobj->userdata;

	Fighter_SetAirborne(fighter_data);

	ActionStateChange(fighter_data->state.frame, 1, 0, gobj, asid_SpecialAirLwAlt, 0x0, 0);

	return;
}

void specialLwAlt_airToGround(GOBJ* gobj) {
	FighterData* fighter_data = gobj->userdata;

	Fighter_SetGrounded2(fighter_data);

	ActionStateChange(fighter_data->state.frame, 1, 0, gobj, asid_SpecialLwAlt, 0x5000, 0);

}

void specialLwAlt_AnimCb(GOBJ* gobj) {
	if (FrameTimerCheck(gobj) == 0){
		Fighter_EnterWait(gobj);
	}
	return;
}

void specialLwAlt_IasaCb(GOBJ* gobj) {
	if (Fighter_CheckJumpInput(gobj) && Fighter_IASACheck_JumpF(gobj)) {
		ActionStateChange(0, 1, 0, gobj, ASID_KNEEBEND, 0, 0);
	}
}

void specialLwAlt_PhysCb(GOBJ* gobj) {
	Fighter_PhysGround_ApplyFriction(gobj);
}

void specialLwAlt_CollCb(GOBJ* gobj) {
	if (Fighter_CollGround_PassLedge(gobj) == 0){
		specialLwAlt_groundToAir(gobj);
	}
}

void specialAirLwAlt_AnimCb(GOBJ* gobj) {
	if (FrameTimerCheck(gobj) == 0){
		Fighter_EnterFall(gobj);
	}
}

void specialAirLwAlt_IasaCb(GOBJ* gobj) {
	if (Fighter_IASACheck_JumpAerial(gobj) && Fighter_CheckJumpInput(gobj)) {
		Fighter_EnterJumpAerial(gobj);
	}
}

void specialAirLwAlt_PhysCb(GOBJ* gobj) {
	Fighter_PhysAir_ApplyGravityFastfall(gobj);
}

void specialAirLwAlt_CollCb(GOBJ* gobj) {
	if (Fighter_CollAir_IgnoreLedge_NoCB(gobj) != 0){
		specialLwAlt_airToGround(gobj);
	}
}


FtState move_logic[] = {
	[0] = {
		.action_id = 295,
		.flags = 0x00340111,
		.move_id = ATKKIND_SPECIALN,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80124908,
		.iasa_callback = 0x80124B6C,
		.physics_callback = 0x80124B74,
		.collision_callback = 0x80124BB4,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[1] = {
		.action_id = 296,
		.flags = 0x00340511,
		.move_id = ATKKIND_SPECIALN,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80124A20,
		.iasa_callback = 0x80124B70,
		.physics_callback = 0x80124B94,
		.collision_callback = 0x80124C20,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[2] = {
		.action_id = 297,
		.flags = 0x00340212,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80124F64,
		.iasa_callback = 0x80124FDC,
		.physics_callback = 0x80124FE4,
		.collision_callback = 0x80125084,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[3] = {
		.action_id = 298,
		.flags = 0x00340212,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x801251BC,
		.iasa_callback = 0x801252FC,
		.physics_callback = 0x8012535C,
		.collision_callback = 0x8012539C,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[4] = {
		.action_id = 300,
		.flags = 0x00340212,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x8012590C,
		.iasa_callback = 0x8012594C,
		.physics_callback = 0x80125954,
		.collision_callback = 0x801259D4,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[5] = {
		.action_id = 301,
		.flags = 0x00340212,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80125B34,
		.iasa_callback = 0x80125BAC,
		.physics_callback = 0x80125BB4,
		.collision_callback = 0x80125C44,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[6] = {
		.action_id = 299,
		.flags = 0x00340212,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x8012557C,
		.iasa_callback = 0x801256B4,
		.physics_callback = 0x801256BC,
		.collision_callback = 0x801256FC,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[7] = {
		.action_id = 302,
		.flags = 0x00340612,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80124FA0,
		.iasa_callback = 0x80124FE0,
		.physics_callback = 0x80125024,
		.collision_callback = 0x801250C0,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[8] = {
		.action_id = 303,
		.flags = 0x00340612,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x8012525C,
		.iasa_callback = 0x8012532C,
		.physics_callback = 0x8012537C,
		.collision_callback = 0x801253D8,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[9] = {
		.action_id = 300,
		.flags = 0x00340612,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80125910,
		.iasa_callback = 0x80125950,
		.physics_callback = 0x80125958,
		.collision_callback = 0x801259D8,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[10] = {
		.action_id = 305,
		.flags = 0x00340612,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80125B70,
		.iasa_callback = 0x80125BB0,
		.physics_callback = 0x80125BF4,
		.collision_callback = 0x80125C80,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[11] = {
		.action_id = 304,
		.flags = 0x00340612,
		.move_id = ATKKIND_SPECIALS,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x8012561C,
		.iasa_callback = 0x801256B8,
		.physics_callback = 0x801256DC,
		.collision_callback = 0x80125738,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[12] = {
		.action_id = 306,
		.flags = 0x00340113,
		.move_id = ATKKIND_SPECIALHI,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80125ED8,
		.iasa_callback = 0x80125F50,
		.physics_callback = 0x80125F58,
		.collision_callback = 0x80125FD8,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[13] = {
		.action_id = 307,
		.flags = 0x00340113,
		.move_id = ATKKIND_SPECIALHI,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80126144,
		.iasa_callback = 0x80126424,
		.physics_callback = 0x801265D4,
		.collision_callback = 0x80126614,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[14] = {
		.action_id = 308,
		.flags = 0x00340113,
		.move_id = ATKKIND_SPECIALHI,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80127198,
		.iasa_callback = 0x801272D8,
		.physics_callback = 0x801272E0,
		.collision_callback = 0x8012738C,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[15] = {
		.action_id = 309,
		.flags = 0x00340513,
		.move_id = ATKKIND_SPECIALHI,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80125F14,
		.iasa_callback = 0x80125F54,
		.physics_callback = 0x80125F78,
		.collision_callback = 0x80126014,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[16] = {
		.action_id = 310,
		.flags = 0x00340513,
		.move_id = ATKKIND_SPECIALHI,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x801262B4,
		.iasa_callback = 0x80126428,
		.physics_callback = 0x801265F4,
		.collision_callback = 0x801267C8,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[17] = {
		.action_id = 311,
		.flags = 0x00340513,
		.move_id = ATKKIND_SPECIALHI,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80127228,
		.iasa_callback = 0x801272DC,
		.physics_callback = 0x80127310,
		.collision_callback = 0x801273D4,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[18] = {
		.action_id = 312,
		.flags = 0x00340014,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80127CDC,
		.iasa_callback = 0x00000000,
		.physics_callback = 0x801280C8,
		.collision_callback = 0x801281EC,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[19] = {
		.action_id = 313,
		.flags = 0x00340014,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80127DE4,
		.iasa_callback = 0x00000000,
		.physics_callback = 0x80128108,
		.collision_callback = 0x8012823C,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[20] = {
		.action_id = 314,
		.flags = 0x00340014,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80127FB0,
		.iasa_callback = 0x00000000,
		.physics_callback = 0x80128148,
		.collision_callback = 0x8012828C,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[21] = {
		.action_id = 315,
		.flags = 0x00340014,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80128050,
		.iasa_callback = 0x00000000,
		.physics_callback = 0x801281AC,
		.collision_callback = 0x801282DC,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[22] = {
		.action_id = 316,
		.flags = 0x00340414,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80127D60,
		.iasa_callback = 0x00000000,
		.physics_callback = 0x801280E8,
		.collision_callback = 0x80128214,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[23] = {
		.action_id = 317,
		.flags = 0x00340414,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80127EC0,
		.iasa_callback = 0x00000000,
		.physics_callback = 0x80128128,
		.collision_callback = 0x80128264,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[24] = {
		.action_id = 318,
		.flags = 0x00340414,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x80128000,
		.iasa_callback = 0x00000000,
		.physics_callback = 0x80128168,
		.collision_callback = 0x801282B4,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[25] = {
		.action_id = 319,
		.flags = 0x00340414,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = 0x8012808C,
		.iasa_callback = 0x00000000,
		.physics_callback = 0x801281CC,
		.collision_callback = 0x80128304,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[26] = {
		.action_id = 320,
		.flags = 0x00340414,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = specialLwAlt_AnimCb,
		.iasa_callback = specialLwAlt_IasaCb,
		.physics_callback = specialLwAlt_PhysCb,
		.collision_callback = specialLwAlt_CollCb,
		.camera_callback = Fighter_UpdateCameraBox,
	},
	[27] = {
		.action_id = 321,
		.flags = 0x00340414,
		.move_id = ATKKIND_SPECIALLW,
		.bitflags1 = 0x00000000,
		.animation_callback = specialAirLwAlt_AnimCb,
		.iasa_callback = specialAirLwAlt_IasaCb,
		.physics_callback = specialAirLwAlt_PhysCb,
		.collision_callback = specialAirLwAlt_CollCb,
		.camera_callback = Fighter_UpdateCameraBox,
	},
};