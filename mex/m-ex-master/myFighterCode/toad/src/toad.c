#include "toad.h"
#include "special_n.c"
#include "special_s.c"
#include "special_hi.c"
#include "special_lw.c"
#include <math.h>
#include "meter.c"

///////////////////////
//     Toad Basic    //
///////////////////////

static ToadPrimaryAttributes toadAttrs1;

//Store Toad's primary attributes
	//This character has a meter which affects these attributes
	//this will let us correctly reset them and change them
void setupPrimaryAttrs(FighterData* fd) { 
	toadAttrs1.aerial_friction = fd->attr.aerial_friction;
	toadAttrs1.aerial_drift_max = fd->attr.aerial_drift_max;
	toadAttrs1.dashrun_terminal_velocity = fd->attr.dashrun_terminal_velocity;
	toadAttrs1.dash_initial_velocity = fd->attr.dash_initial_velocity;
	toadAttrs1.ground_friction = fd->attr.ground_friction;
	toadAttrs1.weight = fd->attr.weight;
	toadAttrs1.hop_v_initial_velocity = fd->attr.hop_v_initial_velocity;
}

//Toad's onLoad function
void OnLoad(GOBJ *gobj)
{
	// get fighter data
	FighterData *fighter_data = gobj->userdata;
	ToadCharVar* charvar = &fighter_data->fighter_var;

	// meter logic and store primary attributes
	GOBJ* meter = setupMeter(gobj);
	charvar->meterGobj = meter;

	setupPrimaryAttrs(fighter_data);

	// copy secondary attributes
	memcpy(fighter_data->special_attributes2, fighter_data->ftData->ext_attr, sizeof(ToadAttr));

	// copy pointer to attributes
	fighter_data->special_attributes = fighter_data->special_attributes2;

	// get fighter item pointer (for ice ball)
	ItemDesc **fighter_items = fighter_data->ftData->items;

	// init ice ball
	MEX_IndexFighterItem(fighter_data->kind, fighter_items[MEX_ITEM_ICEBALL], MEX_ITEM_ICEBALL);
	Fighter_SetCharacterFlags(gobj, 0, 0);
	return;
}

//onSpawn and onRespawn functions to reset character variables
void OnSpawn(GOBJ *gobj)
{
	FighterData *fighter_data = gobj->userdata;
	ToadCharVar *charvar = &fighter_data->fighter_var;

	// clear the fighter flags... something model related...?
	Fighter_SetCharacterFlags(gobj, 0, 0);

	// reset character variables 
	charvar->var3 = 0;
	charvar->stance_framesRemaining = 0;
	charvar->stance = 0;

	return;
}

void OnRespawn(GOBJ* gobj) {
	void (*cb)(GOBJ * gobj) = (void*)0x800E08CC; //mario's original OnRespawn? This is probably unesscessary
	cb(gobj);
	FighterData* fighter_data = gobj->userdata;
	ToadCharVar* charvar = &fighter_data->fighter_var;
	charvar->stance = 0;
	charvar->stance_framesRemaining = 0;
}

void OnDestroy(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	ToadCharVar* charvar = &fd->fighter_var;
	GObj_Destroy(charvar->meterGobj);
	OSReport("Cleared meter in on destroy, meter gobj = %p\n", charvar->meterGobj);
}

//to do power of a number... dont remember why I needed this, but it's fine
double powah(double a, double b) {
	double mreh = 1;
	for (int i = 0; i < b; i++) {
		mreh *= a;
	}
	return mreh;
}

//function to update toad's attributes based on his meter/stance
	//Technically toad can have infinite stances, but Im gonna cap it to like 3
void stanceUp(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	ToadCharVar* charvar = &fd->fighter_var;

	int stance = charvar->stance;
	fd->attr.aerial_friction = toadAttrs1.aerial_friction * (powah(1.05, stance));
	fd->attr.dashrun_terminal_velocity = toadAttrs1.dashrun_terminal_velocity + (0.2 * stance);
	fd->attr.ground_friction = toadAttrs1.ground_friction + (0.00645 * stance);
	fd->attr.dash_initial_velocity = toadAttrs1.dash_initial_velocity + (0.15 * stance);
	fd->attr.weight = toadAttrs1.weight * (powah(0.8975, stance));
	fd->attr.hop_v_initial_velocity = toadAttrs1.hop_v_initial_velocity * (powah(0.9, stance));
	fd->attr.aerial_drift_max = toadAttrs1.aerial_drift_max * (powah(1.075, stance));
}


///table of move logic
__attribute__((used)) static struct FtState move_logic[] = {
	// State: 341 - Animation: FFFFFFFF
	{
		-1,	 // AnimationID
		0x0, // StateFlags
		0x1, // AttackID
		0x0, // BitFlags
		0x0, // AnimationCallback
		0x0, // IASACallback
		0x0, // PhysicsCallback
		0x0, // CollisionCallback
		0x0, // CameraCallback
	},
	// State: 342 - Animation: FFFFFFFF
	{
		-1,	 // AnimationID
		0x0, // StateFlags
		0x1, // AttackID
		0x0, // BitFlags
		0x0, // AnimationCallback
		0x0, // IASACallback
		0x0, // PhysicsCallback
		0x0, // CollisionCallback
		0x0, // CameraCallback
	},
	// State: 343 - SpecialN
	{
		295,						// AnimationID
		0x340111,					// StateFlags
		0x12,						// AttackID
		0x0,						// BitFlags
		SpecialN_AnimationCallback, // AnimationCallback
		SpecialN_IASACallback,		// IASACallback
		SpecialN_PhysicCallback,	// PhysicsCallback
		SpecialN_CollisionCallback, // CollisionCallback
		Fighter_UpdateCameraBox,	// CameraCallback
	},
	// State: 344 - SpecialAirN
	{
		296,						   // AnimationID
		0x340511,					   // StateFlags
		0x12,						   // AttackID
		0x0,						   // BitFlags
		SpecialAirN_AnimationCallback, // AnimationCallback
		SpecialAirN_IASACallback,	   // IASACallback
		SpecialAirN_PhysicCallback,	   // PhysicsCallback
		SpecialAirN_CollisionCallback, // CollisionCallback
		Fighter_UpdateCameraBox,	   // CameraCallback
	},
	// State: 345 - SpecialS
	{
		297,						// AnimationID
		0x341012,					// StateFlags
		0x13,						// AttackID
		0x0,						// BitFlags
		SpecialS_AnimationCallback, // AnimationCallback
		SpecialS_IASACallback,		// IASACallback
		SpecialS_PhysicCallback,	// PhysicsCallback
		SpecialS_CollisionCallback, // CollisionCallback
		Fighter_UpdateCameraBox,	// CameraCallback
	},
	// State: 346 - SpecialSAir
	{
		298,						   // AnimationID
		0x341012,					   // StateFlags
		0x13,						   // AttackID
		0x0,						   // BitFlags
		SpecialAirS_AnimationCallback, // AnimationCallback
		SpecialAirS_IASACallback,	   // IASACallback
		SpecialAirS_PhysicCallback,	   // PhysicsCallback
		SpecialAirS_CollisionCallback, // CollisionCallback
		Fighter_UpdateCameraBox,	   // CameraCallback
	},
	// State: 347 - SpecialHi
	{
		299,						 // AnimationID
		0x340213,					 // StateFlags
		0x14,						 // AttackID
		0x0,						 // BitFlags
		SpecialHi_AnimationCallback, // AnimationCallback
		SpecialHi_IASACallback,		 // IASACallback
		SpecialHi_PhysicCallback,	 // PhysicsCallback
		SpecialHi_CollisionCallback, // CollisionCallback
		Fighter_UpdateCameraBox,	 // CameraCallback
	},
	// State: 348 - SpecialAirHi
	{
		300,							// AnimationID
		0x340613,						// StateFlags
		0x14,							// AttackID
		0x0,							// BitFlags
		SpecialAirHi_AnimationCallback, // AnimationCallback
		SpecialAirHi_IASACallback,		// IASACallback
		SpecialAirHi_PhysicCallback,	// PhysicsCallback
		SpecialAirHi_CollisionCallback, // CollisionCallback
		Fighter_UpdateCameraBox,		// CameraCallback
	},
	// State: 349 - SpecialLw
	{
		301,						 // AnimationID
		0x340214,					 // StateFlags
		0x15,						 // AttackID
		0x0,						 // BitFlags
		SpecialLw_AnimationCallback, // AnimationCallback
		SpecialLw_IASACallback,		 // IASACallback
		SpecialLw_PhysicCallback,	 // PhysicsCallback
		SpecialLw_CollisionCallback, // CollisionCallback
		Fighter_UpdateCameraBox,	 // CameraCallback
	},
	// State: 350 - SpecialAirLw
	{
		302,							// AnimationID
		0x340614,						// StateFlags
		0x15,							// AttackID
		0x0,							// BitFlags
		SpecialAirLw_AnimationCallback, // AnimationCallback
		SpecialAirLw_IASACallback,		// IASACallback
		SpecialAirLw_PhysicCallback,	// PhysicsCallback
		SpecialAirLw_CollisionCallback, // CollisionCallback
		Fighter_UpdateCameraBox,		// CameraCallback
	}
};
