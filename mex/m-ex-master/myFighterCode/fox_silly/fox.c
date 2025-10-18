#include "mex.h"

#define CENTRE_LIMIT 0.2

#define FRAMES_REQUIREMENT 450

#define METER_FILENAME "Meters.dat"
#define METER_SYMBOL "Relax_scene_models"
#define FRAMES_UNTIL_METERFULL 2700

typedef enum StickDirection
{
	STICKDIR_CENTRE,
	STICKDIR_FORWARD,
	STICKDIR_DOWNFORWARD,
	STICKDIR_DOWN,
	STICKDIR_DOWNBACK,
	STICKDIR_BACK,
	STICKDIR_UPBACK,
	STICKDIR_UP,
	STICKDIR_UPFORWARD,
	STICKDIR_COUNT,
}StickDirection;

typedef struct foxAttr
{
	int filler[30];
	int stickTiltTimers[STICKDIR_COUNT];
	int shineFlag;
	int dev_door;
	int framecounter;
} foxAttr;

typedef struct Symbol_WpInd_scene_models
{
	JOBJSet* WpInd_scene_models;
} Symbol_WpInd_scene_models;

typedef struct MeterVars
{
	GOBJ* fighter;
	int* ply;
	int state;
	int framesleft;
	Vec3 stoppos[4];
	Vec3 kb[4];
	int framecounter;
} MeterVars;

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
		foxAttr* charvar = &fighterData->fighter_var;

		jobjay->trans = *Match_GetPlayerHUDPos(fighterData->ply);
		jobjay->trans.X = jobjay->trans.X - 4.6; //-5.04;
		jobjay->trans.Y = jobjay->trans.Y + 2.375;

		int frameCalc = charvar->framecounter / 27;

		DOBJ* myDobj = JOBJ_GetDObj(jobj_CurrCharge);
		MOBJ* myMobj = myDobj->mobj;
		HSD_Material* myMaterial = myMobj->mat;

		GXColor meterColour;
		if (charvar->framecounter > FRAMES_REQUIREMENT) {
			meterColour.r = 255;
			meterColour.g = 0;
			meterColour.b = 0;
			meterColour.a = 175;
		}
		else {
			meterColour.r = 80;
			meterColour.g = 80;
			meterColour.b = 80;
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
	foxAttr* charvar = &fighterData->fighter_var;
	//get meter data
	MeterVars* meterData = tension_gobj->userdata;

	//meter mode reset
	if (charvar->framecounter < 0) {
		charvar->framecounter = 0;
	}
}

void ToadAwsom_Multishine(GOBJ* gobj) {
	FighterData* fighterData = gobj->userdata;
	foxAttr* charvar = &fighterData->fighter_var;
	bool is_legalState = !((fighterData->state_id >= ASID_CATCH && fighterData->state_id <= ASID_CAPTUREFOOT) ||
		(fighterData->state_id >= ASID_THROWNF && fighterData->state_id<= ASID_THROWNLWWOMEN) ||
		(fighterData->state_id >= ASID_SHOULDEREDWAIT && fighterData->state_id <= ASID_BARRELCANNONWAIT) ||
		fighterData->state_id <= ASID_REBIRTHWAIT);
	if (fighterData->input.held & HSD_BUTTON_B && fighterData->input.lstick.Y < -0.6 && fighterData->input.held & HSD_TRIGGER_Z && charvar->shineFlag!=0 && is_legalState && charvar->dev_door != 0) {
		if (fighterData->phys.air_state == 0 && fighterData->state.frame > 2) {
			ActionStateChange(0, 1, 0, gobj, 360, 0x0, 0);
		}
		else if (fighterData->phys.air_state != 0 && fighterData->state.frame > 2) {
			ActionStateChange(0, 1, 0, gobj, 365, 0x0, 0);
		}
		return;
	}
	charvar->shineFlag = 0;
}

void ToadAwsom_StickTiltTimer_Increment(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	foxAttr* charvar = &fd->fighter_var;
	for(int i = 0; i < STICKDIR_COUNT; i++) {
		if (charvar->stickTiltTimers[i] < 255) {
			charvar->stickTiltTimers[i]++;
		}
	}
}

void ToadAwsom_StickTiltTimer_Update(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	foxAttr* charvar = &fd->fighter_var;

	if ((fd->input.lstick.Y < CENTRE_LIMIT && fd->input.lstick.Y > -CENTRE_LIMIT) && (fd->input.lstick.X < CENTRE_LIMIT && fd->input.lstick.X > -CENTRE_LIMIT)) {
		charvar->stickTiltTimers[STICKDIR_CENTRE] = 0;
		return;
	}

	float angle = atan2(fd->input.lstick.Y, fd->input.lstick.X) * (180.0f / M_PI);
	if (angle < 0) angle += 360.0f;

	if (angle > 337.5f || angle < 22.5f) {
		charvar->stickTiltTimers[STICKDIR_FORWARD] = 0;
	}
	else if (angle > 22.5f && angle < 67.5f) {
		charvar->stickTiltTimers[STICKDIR_UPFORWARD] = 0;
	}
	else if (angle > 67.5f && angle < 112.5f) {
		charvar->stickTiltTimers[STICKDIR_UP] = 0;
	}
	else if (angle > 112.5f && angle < 157.5f) {
		charvar->stickTiltTimers[STICKDIR_UPBACK] = 0;
	}
	else if (angle > 157.5f && angle < 202.5f) {
		charvar->stickTiltTimers[STICKDIR_BACK] = 0;
	}
	else if (angle > 202.5f && angle < 247.5f) {
		charvar->stickTiltTimers[STICKDIR_DOWNBACK] = 0;
	}
	else if (angle > 247.5f && angle < 292.5f) {
		charvar->stickTiltTimers[STICKDIR_DOWN] = 0;
	}
	else if (angle > 292.5f && angle < 337.5f) {
		charvar->stickTiltTimers[STICKDIR_DOWNFORWARD] = 0;
	}
}

void ToadAwsom_enableMultishine(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	foxAttr* charvar = &fd->fighter_var;

	if (charvar->stickTiltTimers[STICKDIR_DOWN] < 25 &&
		charvar->stickTiltTimers[STICKDIR_DOWNFORWARD] < 25 &&
		charvar->stickTiltTimers[STICKDIR_FORWARD] < 25 &&
		charvar->stickTiltTimers[STICKDIR_FORWARD] > charvar->stickTiltTimers[STICKDIR_DOWNFORWARD] &&
		charvar->stickTiltTimers[STICKDIR_DOWNFORWARD] > charvar->stickTiltTimers[STICKDIR_DOWN]) {
		charvar->shineFlag = 1;
	}
	else if (charvar->stickTiltTimers[STICKDIR_DOWN] < 25 &&
		charvar->stickTiltTimers[STICKDIR_DOWNBACK] < 25 &&
		charvar->stickTiltTimers[STICKDIR_BACK] < 25 &&
		charvar->stickTiltTimers[STICKDIR_BACK] > charvar->stickTiltTimers[STICKDIR_DOWNBACK] &&
		charvar->stickTiltTimers[STICKDIR_DOWNBACK] > charvar->stickTiltTimers[STICKDIR_DOWN]) {
		charvar->shineFlag = 1;
	}
}

void ToadAwsom_StickTiltTimer_Debug(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	foxAttr* charvar = &fd->fighter_var;

	OSReport("=== Stick Tilt Timers ===\n");
	OSReport("Centre: %d\n", charvar->stickTiltTimers[STICKDIR_CENTRE]);
	OSReport("Forward: %d\n", charvar->stickTiltTimers[STICKDIR_FORWARD]);
	OSReport("UpForward: %d\n", charvar->stickTiltTimers[STICKDIR_UPFORWARD]);
	OSReport("Up: %d\n", charvar->stickTiltTimers[STICKDIR_UP]);
	OSReport("UpBack: %d\n", charvar->stickTiltTimers[STICKDIR_UPBACK]);
	OSReport("Back: %d\n", charvar->stickTiltTimers[STICKDIR_BACK]);
	OSReport("DownBack: %d\n", charvar->stickTiltTimers[STICKDIR_DOWNBACK]);
	OSReport("Down: %d\n", charvar->stickTiltTimers[STICKDIR_DOWN]);
	OSReport("DownForward: %d\n", charvar->stickTiltTimers[STICKDIR_DOWNFORWARD]);

	float angle = atan2(fd->input.lstick.Y, fd->input.lstick.X) * (180.0f / M_PI);
	if (angle < 0) angle += 360.0f;
	OSReport("Stick X: %.2f, Y: %.2f, Angle: %.1f\n", fd->input.lstick.X, fd->input.lstick.Y, angle);
	OSReport("========================\n");
}

void ToadAwsom_LaserLogic(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	foxAttr* charvar = &fd->fighter_var;
	if (Pause_CheckStatus(1) != 2) {
		if (charvar->framecounter < FRAMES_UNTIL_METERFULL) {
			if (fd->phys.air_state != 0) charvar->framecounter += 0.2;
			else charvar->framecounter += 1.75;
		}
	}
}

void onactionstatechange(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	if (fd->state_id == 342 || fd->state_id == 345) {
		fd->fighter_var.ft_var52 -= FRAMES_REQUIREMENT;
	}
}

void SpecialAirN(GOBJ* gobj) {
	FighterData* fp = gobj->userdata;
	foxAttr* charvar = &fp->fighter_var;
	if (charvar->framecounter < FRAMES_REQUIREMENT) {
		Fighter_EnterSpecialFall(gobj, 1, 1, 0, 0.6, 30);
	}
	else {
		void (*fox_enterSpecialN)(GOBJ*) = (void*)0x800E61A8;
		fox_enterSpecialN(gobj);
	}
}

void SpecialN(GOBJ* gobj) {
	FighterData* fp = gobj->userdata;
	foxAttr* charvar = &fp->fighter_var;
	if (charvar->framecounter < FRAMES_REQUIREMENT) {
		Fighter_SetAirborne(fp);
		fp->phys.self_vel.Y = 0.2;
		Fighter_EnterDamageFall(gobj);
	}
	else {
		void (*fox_enterSpecialN)(GOBJ*) = (void*)0x800E608C;
		fox_enterSpecialN(gobj);
	}
}

void onFrame(GOBJ* gobj) {
	FighterData* fighterData = gobj->userdata;
	foxAttr* charvar = &fighterData->fighter_var;
	
	ToadAwsom_StickTiltTimer_Increment(gobj);
	ToadAwsom_StickTiltTimer_Update(gobj);
	//ToadAwsom_StickTiltTimer_Debug(gobj);
	ToadAwsom_enableMultishine(gobj);
	ToadAwsom_Multishine(gobj);
	ToadAwsom_LaserLogic(gobj);
}

void onLoad(GOBJ* gobj) {
	void (*onload)(GOBJ * gobj) = (void*)0x800E57AC;
	onload(gobj);

	FighterData* fd = gobj->userdata;
	setupMeter(gobj);
}

void onSpawn(GOBJ* gobj) {
	void (*onspawn)(GOBJ * gobj) = (void*)0x800E5554;
	onspawn(gobj);
	FighterData* fd = gobj->userdata;
	foxAttr* charvar = &fd->fighter_var;
	charvar->shineFlag = 0;
	for (int i = 0; i < STICKDIR_COUNT; i++) {
		charvar->stickTiltTimers[i] = 0;
	}
	charvar->dev_door = 1;
	charvar->framecounter = 0;
}

void onRespawn(GOBJ* gobj) {
	void (*onspawn)(GOBJ * gobj) = (void*)0x800E5554;
	onspawn(gobj);
	FighterData* fd = gobj->userdata;
	foxAttr* charvar = &fd->fighter_var;
	charvar->shineFlag = 0;
	for (int i = 0; i < STICKDIR_COUNT; i++) {
		charvar->stickTiltTimers[i] = 0;
	} 
	charvar->dev_door = 1;
	charvar->framecounter = 0;
}
