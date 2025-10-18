#ifndef FT_CUP_H
#define FT_CUP_H

#include "mex.h"

#define STAGE_DOBJ_COUNT 2
#define FRAMES_TO_CHANGECOLOUR 2000
#define STAGE_COLOURCHANGE_PERFRAME_CONSTANT 60
#define STAGE_DOBJ_COUNT 2
#define STAGE_INFO_ADDR ((Stage*)0x8049E6C8)

static int stageType_tracker;
static int frameCounter = 0;
static GXColor stage_targetColour[STAGE_DOBJ_COUNT];
static int* grNLa_804D6AD0;

enum stageType {
	BLUE = 0,
	PURPLE,
	BLACK,
	WHITE,
	RED
};

static GXColor colourDefinitions[] = {
	{ 0, 0, 255, 255 }, { 67, 22, 181, 255 }, { 0, 0,0,255 }, { 255,255,255,255 }, { 255,0,0,255 },
};

enum colourChange_Debug {
	NO_ERROR = 0,
	FAILED_GET_JOBJ,
	FAILED_GET_DOBJ,
	FAILED_GET_MOBJ,
	FAILED_GET_MATERIAL
};

#define MAPVARS(mapData) (*(struct Map_GroundVars*)(((char*)(mapData)) + 0xC4))
#define LASTVARS(mapData) (*(struct Last_GroundVars*)(((char*)(mapData)) + 0xC4))
struct Map_GroundVars {
	u32 unk2_stageEffect_var : 1;
	u32 unk_stageEffect_var : 1;
	u32 MAIN_SWITCH : 16;
	u32 xC4_b26 : 1;
	u32 xC4_b27 : 1;
	u32 xC4_b28 : 1;
	u32 xC4_b29 : 1;
	u32 xC4_b30 : 1;
	u32 xC4_b31 : 1;
	float xC8;
	GOBJ* lv_gobj[6];
	float xE4;
	float xE8;
	float xEC;
	float xF0;
	float xF4;
	float xF8;
	float xFC;
	float x100;
	float x104;
};
struct Last_GroundVars {
	/* +00 gp+C4    */ float xC4;
	/* +04 gp+C8    */ float xC8;
	/* +08 gp+CC    */ float xCC;
	/* +0C gp+D0    */ float xD0;
	/* +10 gp+D4    */ float xD4;
	/* +14 gp+D8    */ float xD8;
	/* +18 gp+DC    */ float xDC;
	/* +1C gp+E0    */ void* xE0;
};

#endif