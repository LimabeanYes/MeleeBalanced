#include "mex.h"

#include "mex.h"

#define METER_FILENAME "Meters.dat"
#define METER_SYMBOL "Relax_scene_models"
#define FRAMES_UNTIL_METERFULL 1800
#define OVERHEAT_FRAMES_REQUIREMENT  1500

typedef struct foxvars {
	int filler0[48];
	float overheat;
}foxvars;

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

			jobjay->trans = *Match_GetPlayerHUDPos(fighterData->ply);
			jobjay->trans.X = jobjay->trans.X - 4.6; //-5.04;
			jobjay->trans.Y = jobjay->trans.Y + 0.95;

			foxvars* foxVar = &fighterData->fighter_var;
			int frameCalc = foxVar->overheat / 18;

			DOBJ* myDobj = JOBJ_GetDObj(jobj_CurrCharge);
			MOBJ* myMobj = myDobj->mobj;
			HSD_Material* myMaterial = myMobj->mat;

			GXColor meterColour;
			if (foxVar->overheat >= OVERHEAT_FRAMES_REQUIREMENT) {
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

//setup meter gobj
GOBJ* setupMeter(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	foxvars* foxVar = &fd->fighter_var;
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

	//get meter data
	MeterVars* meterData = tension_gobj->userdata;
	foxvars* foxVar = &fighterData->fighter_var;
}

void onFrame(GOBJ* gobj) {
	FighterData* fighterData = gobj->userdata;
	//meter behaviour
	foxvars* foxVar = &fighterData->fighter_var;
	if (Pause_CheckStatus(1) != 2) {
		if (fighterData->phys.air_state != 0) {
			if (foxVar->overheat <= FRAMES_UNTIL_METERFULL) {
				foxVar->overheat += 1;
			}
		}
		else if (fighterData->phys.air_state == 0) foxVar->overheat -= 2;
		
		if (foxVar->overheat > OVERHEAT_FRAMES_REQUIREMENT) {
			Fighter_GiveDamage(fighterData, 0.0075);
		}
		if (foxVar->overheat < 0) {
			foxVar->overheat = 0;
		}
	}
	OSReport("Overheat: %f\n", foxVar->overheat);
}



void onLoad(GOBJ* gobj) {
	void (*onload)(GOBJ * gobj) = (void*)0x8013C67C;
	onload(gobj);

	FighterData* fd = gobj->userdata;
	setupMeter(gobj);
}
void onSpawn(GOBJ* gobj) {
	void (*onspawn)(GOBJ * gobj) = (void*)0x8013C318;
	onspawn(gobj);
	FighterData* fd = gobj->userdata;
	foxvars* foxVar = &fd->fighter_var;
	foxVar->overheat = 0;
}
void onRespawn(GOBJ* gobj) {
	void (*onspawn)(GOBJ * gobj) = (void*)0x8013C318;
	onspawn(gobj);
	FighterData* fd = gobj->userdata;
	foxvars* foxVar = &fd->fighter_var;
	foxVar->overheat = 0;
}
