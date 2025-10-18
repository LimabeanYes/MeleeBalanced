#include "rng.h"
#include "antigrav.c"
#include "alteredSpeed.c"
#include "slippery.c"

////////////////////////////////////////
//  GOBJ 0 callbacks: General Points  //
////////////////////////////////////////

void Points_OnCreation(GOBJ* map)
{
	MapData* md = map->userdata;
	Stage_MapStateChange(map, md->index, 0);
	return;
}
int Points_OnDeletion(GOBJ* map)
{
	return 0;
}
void Points_OnFrame(GOBJ* map)
{
	return;
}
void Points_OnUnk(GOBJ* map)
{
	return;
}

///////////////////////////////////////
//  GOBJ 1 callbacks - unesscessary  //
///////////////////////////////////////

////////////////////////////////
//  GOBJ 2 callbacks: ground  //
////////////////////////////////

// helper functions
static inline void manage_frameCounter_reset() { frameCounter = 0; }

void manage_checkForEventStart() {
	if (frameCounter >= gr_param->frames_until_rng_event) {
		manage_frameCounter_reset();
		int randEvent = HSD_Randi(RNG_EVENT_COUNT - 1) + 1;
		if(IS_DEBUG!=0) OSReport("RNG Event Number: %d\n", randEvent);
		switch (randEvent) {
		case ANTIGRAVITY:
			if (IS_DEBUG != 0) OSReport("RNG Event: Antigravity!\n");
			rngEventActive = ANTIGRAVITY;
			randEvent_Antigravity_Apply();
			break;
		case SPEEDUP:
			if (IS_DEBUG != 0) OSReport("RNG Event: Speed Up!\n");
			rngEventActive = SPEEDUP;
			randEvent_speedAlter_apply();
			randEvent_speedAlter_onFrame();
			break;
		case SLOWDOWN:
			if (IS_DEBUG != 0) OSReport("RNG Event: Slow Down!\n");
			rngEventActive = SLOWDOWN;
			randEvent_speedAlter_apply();
			randEvent_speedAlter_onFrame();
			break;
		case SLIPPERY:
			if (IS_DEBUG != 0) OSReport("RNG Event: Slippery!\n");
			rngEventActive = SLIPPERY;
			randEvent_slippery_Apply();
			break;
		default:
			if (IS_DEBUG != 0) OSReport("manage_eventInProgress entered unhandled state?\n");
			break;
		}
	}
}

void manage_eventInProgress() {
	switch (rngEventActive) {
	case ANTIGRAVITY:
		if (frameCounter >= gr_param->antigrav_attributes.frames_until_antigrav_ends) {
			manage_frameCounter_reset();
			randEvent_Antigravity_Kill();
			rngEventActive = NOEVENT;
		}
		break;
	case SPEEDUP:
	case SLOWDOWN:
		if (frameCounter >= gr_param->alterspeedAttrs.frames_until_speed_ends) {
			manage_frameCounter_reset();
			randEvent_speedAlter_Kill();
			rngEventActive = NOEVENT;
		}
		else {
			randEvent_speedAlter_onFrame();
		}
		break;
	case SLIPPERY:
		if(frameCounter >= gr_param->slippery_attributes.frames_until_slippery_ends) {
			manage_frameCounter_reset();
			randEvent_slippery_Kill();
			rngEventActive = NOEVENT;
		}
		break;
	default:
		if (IS_DEBUG != 0) OSReport("manage_eventInProgress entered unhandled state?\n");
		manage_frameCounter_reset();
		rngEventActive = NOEVENT;
		break;
	}
}

// actual callbacks
void stage_OnCreation_GObj2(GOBJ* gobj) {

	//RNG_STAGE_SECONDARY_ATTRS* yakumono = gr_param;
	frameCounter = 0;
	rngEventActive = NOEVENT;
}
int stage_OnDeletion_GObj2(GOBJ* gobj) {
	return 0;
}
void stage_OnFrame_GObj2(GOBJ* gobj) {
	if(Pause_CheckStatus(1) != 2) frameCounter++;

	if (rngEventActive == NOEVENT) {
		manage_checkForEventStart();
	}
	else {
		manage_eventInProgress();
	}
}
void stage_OnUnk_GObj2(GOBJ* gobj) {
	return;
}

///////////////////////////
//  GOBJ callback table  //
///////////////////////////

__attribute__((used))
static struct MapDesc map_gobjs[] = {
	// map gobj 0
	{
		.onCreation = Points_OnCreation,
		.onDeletion = Points_OnDeletion,
		.onFrame = Points_OnFrame,
		.onUnk = Points_OnUnk,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 1
	{
		.onCreation = 0x80223ABC,
		.onDeletion = 0x80223B0C,
		.onFrame = 0x80223B14,
		.onUnk = 0x80223B34,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 2
	{
		.onCreation = stage_OnCreation_GObj2,
		.onDeletion = stage_OnDeletion_GObj2,
		.onFrame = stage_OnFrame_GObj2,
		.onUnk = stage_OnUnk_GObj2,
		.is_lobj = 1,
		.is_fog = 1,
		.is_cobj = 0,
	},
	// map gobj 3
	{
		.onCreation = 0x0       ,
		.onDeletion = 0x0       ,
		.onFrame = 0x0       ,
		.onUnk = 0x0       ,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
};

//////////////////////
//  Main Callbacks  //
//////////////////////

void OnInit()
{
	// get yakumono (Stage parameters)
	gr_param = Stage_GetYakumonoParam();

	if (gr_param == 0)
		__assert("rng.c", __LINE__, "yakumono node not found");

	// create map gobjs
	Stage_CreateMapGObj(STAGE_COLL);
	Stage_CreateMapGObj(STAGE_BACKGROUND);
	Stage_CreateMapGObj(STAGE_GROUND);

	// init camera and blastzones
	Stage_CameraLimitInitialization();
	Stage_BlastzoneInitialization();

	return;
}
void OnGO()
{
	return;
}
void OnLoad()
{
	return;
}
void* onTouchLine(int line_id)
{
	return 0;
}
void OnUnk1()
{
	return 0;
}
int OnUnk2()
{
	return 0;
}
int OnUnk4()
{
	return 1;
}