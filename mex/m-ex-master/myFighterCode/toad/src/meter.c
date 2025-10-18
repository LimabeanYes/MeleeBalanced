#include "toad.h"
#include "debug.c"

//I should have commented on this when I was working on it
//cuz now i dont really remember what half this does

//setup meter gobj
GOBJ* setupMeter(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;

	//load meter file
	setupMeter_debug(0);
	HSD_Archive* meterArchive = Archive_LoadFile(METER_FILENAME);
	if (meterArchive !=0) setupMeter_debug(1);

	//load symbol, setup jobj
	setupMeter_debug(2);
	Symbol_WpInd_scene_models* meterModel = Archive_GetPublicAddress(meterArchive, METER_SYMBOL);
	if (meterModel != 0) {
		setupMeter_debug(3);
	}
	JOBJSet* jobjset_WpInd = meterModel->WpInd_scene_models;

	//gobj setup
	GOBJ* gobj_WpInd = JOBJ_LoadSet(0, jobjset_WpInd, 0, 0, 0, 11, 1, meterLogic);
	void* UserData = calloc(sizeof(MeterVars));
	GObj_AddUserData(gobj_WpInd, 4, HSD_Free, UserData);
	setupMeter_debug(4);

	//var setup
	MeterVars* meterData = gobj_WpInd->userdata;
	meterData->fighter = gobj;
	meterData->ply = fd->ply;
	setupMeter_debug(4);
	return gobj_WpInd;
}

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
		ToadCharVar* charvar = &fighterData->fighter_var;

		jobjay->trans = *Match_GetPlayerHUDPos(fighterData->ply);
		jobjay->trans.X = jobjay->trans.X - 4.6; //-5.04;
		jobjay->trans.Y = jobjay->trans.Y + 2.375;

		int frameCalc = charvar->stance_framesRemaining / 12;

		DOBJ* myDobj = JOBJ_GetDObj(jobj_CurrCharge);
		MOBJ* myMobj = myDobj->mobj;
		HSD_Material* myMaterial = myMobj->mat;

		GXColor meterColour = myMaterial->diffuse;
		meterColour.r = ((255/STANCE_MAX) * (charvar->stance));
		meterColour.g = ((255/(STANCE_MAX*12)) * (charvar->stance));
		meterColour.b = 255 - ((255 / STANCE_MAX) * (charvar->stance));
		meterColour.a = 175;
		myMaterial->diffuse = meterColour;
		myMaterial->specular = meterColour;
		//OSReport("R: %d, G: %d, B: %d, A: %d\n", meterColour.r, meterColour.g, meterColour.b, meterColour.a);
		//myMaterial->ambient = (GXColor){ 0,0,0,255 };
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

void RelaxOnfame(GOBJ* fighter_gobj, GOBJ* tension_gobj)
{
	//get toad data
	FighterData* fighterData = fighter_gobj->userdata;
	ToadCharVar* charvar = &fighterData->fighter_var;

	//get meter data
	MeterVars* meterData = tension_gobj->userdata;

	//if frames remaining for stance somehow goes below 0, set it to 0
	if (charvar->stance_framesRemaining < 0) charvar->stance_framesRemaining = 0;

	/**
	* If toad is in a stance, -1 from framesRemaining every frame
	* if 0 frames remaining, drop stance by 1. If toad is still in a stance, reset framesRemaining to 1200 (20 seconds)
	* Shouldnt reduce stance while paused
	**/
	if (Pause_CheckStatus(1) != 2) {
		if (charvar->stance != 0) {
			if (charvar->stance_framesRemaining != 0) {
				charvar->stance_framesRemaining--;
			}
			else {
				charvar->stance--;
				if (charvar->stance > 0) {
					charvar->stance_framesRemaining = 1200;
				}
			}
		}
		else if (charvar->stance < 0) { //if stance drops below 0, make sure it's set to 0
			charvar->stance = 0;
		}
	}
	stanceUp(fighter_gobj);	//function to apply attributes based on stance
}

void onFrame(GOBJ* gobj) {
	return;
}