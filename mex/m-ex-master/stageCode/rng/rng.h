#ifndef FT_RNG_H
#define FT_RNG_H

#include "mex.h"

#define IS_DEBUG 1 // For OSReport debug messages

///////////////////////////
//  Important variables  //
///////////////////////////

static int frameCounter;
static int rngEventActive;
static struct RNG_STAGE_SECONDARY_ATTRS* gr_param;
static float ogAttribute[4];

/////////////////////////////
//  Function Declarations  //
/////////////////////////////

//Antigravity
void randEvent_Antigravity_Apply();
void randEvent_Antigravity_Kill();

//Altered Speed
void randEvent_speedAlter_apply();
void randEvent_speedAlter_onFrame();
void randEvent_speedAlter_Kill();

//Slippery
void randEvent_slippery_Kill();
void randEvent_slippery_Apply();

///////////////////////
//  important enums  //
///////////////////////

enum RNG_EVENTS {
	//Random events that happen on this stage
	NOEVENT,
	ANTIGRAVITY,
	SPEEDUP,
	SLOWDOWN,
	SLIPPERY,
	RNG_EVENT_COUNT
};

enum STAGE_ELEMENTS {
	STAGE_COLL,
	STAGE_BACKGROUND,
	STAGE_GROUND
};

////////////////////////////
//  Secondary Attributes  //
////////////////////////////

typedef struct ALTERSPEED_ATTRS {
	int frames_until_speed_ends; //0xC
	float speedAlterAmount_fast; //0x10
	float speedAlterAmount_slow; //0x14
}ALTERSPEED_ATTRS;

typedef struct ANTIGRAV_ATTRS {
	int frames_until_antigrav_ends; //0x4
	float antigrav_strength; //0x8
}ANTIGRAV_ATTRS;

typedef struct SLIPPERY_ATTRS {
	int frames_until_slippery_ends; //0x18
	float friction_multiplier; //0x1C
}SLIPPERY_ATTRS;

typedef struct RNG_STAGE_SECONDARY_ATTRS {
	int frames_until_rng_event; //0x0
	ANTIGRAV_ATTRS antigrav_attributes; //0x4
	ALTERSPEED_ATTRS alterspeedAttrs; //0xC
	SLIPPERY_ATTRS slippery_attributes; //0x18
} RNG_STAGE_SECONDARY_ATTRS;

#endif