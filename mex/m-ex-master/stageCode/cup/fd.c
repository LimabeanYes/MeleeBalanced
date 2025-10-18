#include "mex.h"

#define STAGE_INFO_ADDR ((Stage*)0x8049E6C8)
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))
static struct MapDesc map_gobjs[];
static int* grNLa_804D6AD0;
#define HSD_ASSERT(line, cond)                                                \
    ((cond) ? ((void) 0) : __assert(__FILE__, line, #cond))

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
static inline struct Map_GroundVars* GetMapGroundVars(struct MapData* mapData) {
	// 0xC4 is the offset in M-Ex MapData where map_var starts
	return (struct Map_GroundVars*)((char*)mapData + 0xC4);
}
static GOBJ* grLast_8021A7F4(int id);

static void (*someFogCb)(GXColor*) = (void*)0x801C2090;
////////////////
// gobj 0 cbs //
////////////////

void onCreation_gobj0(GOBJ* gobj) {
	MapData* md = gobj->userdata;
	Stage_MapStateChange(gobj, md->index, 0);

}
void onDeletion_gobj0(GOBJ* gobj) { return 0; }
void onframe_gobj0(GOBJ* gobj) {}

////////////////
// gobj 1 cbs //
////////////////

void onCreation_gobj1(GOBJ* gobj) {
	MapData* md = gobj->userdata;
	Stage_MapStateChange(gobj, md->index, 0);
	md->render_kind = 1;
}
void onDeletion_gobj1(GOBJ* gobj) { return 0; }
void onFrame_gobj1(GOBJ* gobj) {}

////////////////
// gobj 2 cbs //
////////////////

void onCreation_gobj2(GOBJ* gobj) {
	MapData* md = gobj->userdata;
	Stage_MapStateChange(gobj, md->index, 0);
}
void onDeletion_gobj2(GOBJ* gobj) { return 0; }
void onframe_gobj2(GOBJ* gobj) {}

////////////////
// gobj 3 cbs //
////////////////
#define SKIPTOFRAME 180
static void (*grAnime_801C8098)(GOBJ*, int, int, int, float, float) = (void*)0x801C8098;
static void (*grAnime_801C7980)(GOBJ*, int, int) = (void*)0x801C7980;
static s16 grNLa_803E8010[][4] = {
	{ 4, 1, 2, 0 }, { 5, 1, 2, 4 },  { 6, 1, 2, 6 },
	{ 7, 1, 2, 8 }, { 8, 1, 2, 10 }, { 9, 0, -1, 0 },
};
static inline void do_anime(GOBJ* gobj, int i, int n)
{
	if (grNLa_803E8010[i][2] != -1) {
		grAnime_801C8098(gobj, grNLa_803E8010[i][1], 7, n, SKIPTOFRAME, 1);
		grAnime_801C7980(gobj, grNLa_803E8010[i][1], 7);
	}
	else {
		Stage_SetMapJOBJAnim(gobj, grNLa_803E8010[i][1], 7, n, 0, 1);
	}
}
static inline bool animate_all(MapData* gp)
{
	int i;
	void* (*grAnime_801C83D0)(GOBJ*, int, int) = (void*)0x801C83D0;
	for (i = 0; i < 5; i++) {
		if (!grAnime_801C83D0(MAPVARS(gp).lv_gobj[i], grNLa_803E8010[i][1], 7)) {
			return false;
		}
	}
	return true;
}
static void setBubbleColour(void)
{
	GXColor sp8 = { 0x0C, 0x06, 0x28, 0xFF };
	Stage_SetBubbleColorTopLeft(&sp8);
	Stage_SetBubbleColorTopCenter(&sp8);
	Stage_SetBubbleColorTopRight(&sp8);
	Stage_SetBubbleColorMiddleLeft(&sp8);
	Stage_SetBubbleColorMiddleCenter(&sp8);
	Stage_SetBubbleColorMiddleRight(&sp8);
	Stage_SetBubbleColorBottomLeft(&sp8);
	Stage_SetBubbleColorBottomCenter(&sp8);
	Stage_SetBubbleColorBottomRight(&sp8);
}
static void grLast_8021C40C(GOBJ* gobj, GXColor color, float arg2)
{
	GXColor sp18;
	MapData* gp = gobj->userdata;
	someFogCb(&sp18);
	MAPVARS(gp).xE4 = color.r;
	MAPVARS(gp).xE8 = color.g;
	MAPVARS(gp).xEC = color.b;
	MAPVARS(gp).xF4 = sp18.r;
	MAPVARS(gp).xF8 = sp18.g;
	MAPVARS(gp).xFC = sp18.b;
	MAPVARS(gp).x104 = arg2;
	MAPVARS(gp).xC4_b27 = false;
}
static void grLast_8021C6AC(void)
{
	GXColor sp1C = { 0x8C, 0xB4, 0xBE, 0xFF };
	GXColor sp18 = { 0x96, 0xB4, 0xBE, 0xFF };
	GXColor sp14 = { 0x6E, 0x78, 0x8C, 0xFF };
	GXColor sp10 = { 0x00, 0x00, 0x00, 0xFF };
	GXColor spC = { 0x73, 0xA0, 0x91, 0xFF };
	GXColor sp8 = { 0x87, 0xA5, 0xA0, 0xFF };
	Stage_SetBubbleColorTopLeft(&sp1C);
	Stage_SetBubbleColorTopCenter(&sp18);
	Stage_SetBubbleColorTopRight(&sp1C);
	Stage_SetBubbleColorMiddleLeft(&sp14);
	Stage_SetBubbleColorMiddleCenter(&sp10);
	Stage_SetBubbleColorMiddleRight(&sp14);
	Stage_SetBubbleColorBottomLeft(&spC);
	Stage_SetBubbleColorBottomCenter(&sp8);
	Stage_SetBubbleColorBottomRight(&spC);
}
static void stageEffectsAndVars(GOBJ* gobj)
{
	GXColor sp30;
	GXColor sp2C;
	MapData* gp;
	float temp_f1;
	MapData* temp_gp;

	gp = gobj->userdata;
	if (MAPVARS(gp).xC8 > 1800.0F) {
		MAPVARS(gp).xC4_b26 = 1;  // set bit 26
	}
	MAPVARS(gp).xC8 += 1.0F;
	switch (MAPVARS(gp).MAIN_SWITCH) {
	case 9:
		temp_gp = (MapData*)(MAPVARS(gp).lv_gobj[3])->userdata;
		LASTVARS(temp_gp).xDC += 1.0F / 180;
		if (LASTVARS(temp_gp).xDC > 1) {
			LASTVARS(temp_gp).xDC = 1;
		}
		break;
	case 10:
		temp_gp = (MapData*)(MAPVARS(gp).lv_gobj[3])->userdata;
		LASTVARS(temp_gp).xDC -= 1.0F / 58;
		if (LASTVARS(temp_gp).xDC < 0) {
			LASTVARS(temp_gp).xDC = 0;
		}
		//ScreenRumble_Execute(1, 0);
		break;
	case 11:
		//ScreenRumble_Execute(1, 0);
		break;
	case 15:
		if (MAPVARS(gp).xC4_b27) {
			int tmp;
			someFogCb(&sp2C);
			do {
				sp30.r = HSD_Randi(2) * 0x1E;
				sp30.g = HSD_Randi(2) * 0x1E;
				sp30.b = HSD_Randi(2) * 0x1E;
			} while (
				(sp30.r == 0x1E && sp30.g == 0x1E && sp30.b == 0x1E) ||
				(sp30.r == sp2C.r && sp30.g == sp2C.g && sp30.g == sp2C.g));
			tmp = HSD_Randi(0x3C);
			tmp += 0x3C;
			void (*someRGBCb)(GOBJ * gobj, GXColor color, float arg2) = (void*)0x8021C40C;
			someRGBCb(gobj, sp30, tmp);
		}
		break;
	}
	void (*rgbAndVarChanges)(GOBJ * gobj) = (void*)0x8021C500;
	rgbAndVarChanges(gobj);
}
static int state_machine(GOBJ* gobj)
{
	MapData* gp;
	int i;
	int result;
	int unused[4];
	AOBJ* aobj = 0;
	void* (*grLib_801C96E8)(GOBJ*) = (void*)0x801C96E8;
	result = 0;
	gp = gobj->userdata;
	switch (MAPVARS(gp).MAIN_SWITCH) {
	case 1:
		result = 2;
		break;
	case 2:
		if (animate_all(gp)) {
			result = 3;
		}
		break;
	case 3:
		result = 4;
		break;
	case 4:
		if (animate_all(gp)) {
			result = 5;
		}
		break;
	case 5:
		result = 6;
		break;
	case 6:
		if (animate_all(gp)) {
			result = 7;
		}
		break;
	case 7:
		result = 8;
		break;
	case 8:
		if (animate_all(gp)) {
			result = 9;
		}
		break;
	case 9:
		void* (*grAnime_801C8318)(GOBJ*, int, int) = (void*)0x801C8318;
		aobj = grAnime_801C8318(MAPVARS(gp).lv_gobj[3], grNLa_803E8010[3][2], 7);
		HSD_ASSERT(0x3F4, aobj);
		if (aobj->curr_frame == 100) {
			result = 10;
		}
		break;
	case 10:
		if (Stage_CheckAnimEnd2(MAPVARS(gp).lv_gobj[3], grNLa_803E8010[3][2], 7)) {
			result = 11;
		}
		break;
	case 11:
		if (animate_all(gp)) {
			result = 12;
		}
		break;
	case 12:
		result = 13;
		break;
	case 13:
		if (MAPVARS(gp).xC4_b27 && grLib_801C96E8(MAPVARS(gp).lv_gobj[4])) {
			result = 14;
		}
		break;
	case 14:
		if (grLib_801C96E8(MAPVARS(gp).lv_gobj[5])) {
			result = 15;
		}
		break;
	case 15:
		result = 16;
		break;
	case 16:
		if (MAPVARS(gp).xC4_b27 && grLib_801C96E8(MAPVARS(gp).lv_gobj[5])) {
			result = 17;
		}
		break;
	case 17:
		if (grLib_801C96E8(MAPVARS(gp).lv_gobj[0])) {
			result = 1;
		}
		break;
	}
	return result;
}
static inline void grlib_inline(MapData* gp)
{
	psKillGeneratorEZ(LASTVARS(gp).xE0);
	LASTVARS(gp).xE0 = 0;
}
static void transition_machine(GOBJ* gobj_, int arg1)
{
	GOBJ* gobj = gobj_;
	Vec3 sp40;
	u8 _[0x0C];
	MapData* gp;
	int i;
	MapData* temp_r28_10;

	gp = gobj->userdata;

	void* (*Ground_801C1E00)(GOBJ*) = (void*)0x801C1E00;
	void* (*grMaterial_801C9698)(GOBJ*) = (void*)0x801C9698;
	void* (*grAnime_801C7A94)(GOBJ*, int, int, float) = (void*)0x801C7A94;
	void* (*grLib_801C9854)(GOBJ*) = (void*)0x801C9854;
	GXColor grNLa_804DBBD4 = { 0xAA, 0xCA, 0xFF, 0x00 };
	GXColor grNLa_804DBBD8 = { 0xC8, 0xC8, 0xC8, 0xFF };
	MAPVARS(gp).xC8 = 0.0F;
	MAPVARS(gp).MAIN_SWITCH = arg1;
	switch (MAPVARS(gp).MAIN_SWITCH) {
	case 1:
		for (i = 0; i < 5; i++) {
			if (MAPVARS(gp).lv_gobj[i] == 0) {
				MAPVARS(gp).lv_gobj[i] = grLast_8021A7F4(grNLa_803E8010[i][0]);
				HSD_ASSERT(0x44B, MAPVARS(gp).lv_gobj[i]);
				GObj_CopyGXPri(MAPVARS(gp).lv_gobj[i], gobj_);
				if (grNLa_803E8010[i][2] != -1) {
					Stage_SetMapJOBJAnim(MAPVARS(gp).lv_gobj[i], grNLa_803E8010[i][2], 7, grNLa_803E8010[i][3], 0.0F, 1.0F);
				}
				do_anime(MAPVARS(gp).lv_gobj[i], i, 0);
			}
		}
		grAnime_801C8098(Stage_GetMapGObj(4), 0x10, 7, 0, 0.0F, 1.0F);
		MAPVARS(gp).xC4_b26 = 0;
		setBubbleColour();
		break;
	case 2:
		i = 0;
		for (i = 0; i < 5; i++) {
			do_anime(MAPVARS(gp).lv_gobj[i], i, 1);
		}
		grAnime_801C7A94(Stage_GetMapGObj(4), 0x10, 7, 0.0F);
		grLib_801C9854(Stage_GetMapGObj(4)->hsd_object);
		MAPVARS(gp).xC4_b26 = 1;
		break;
	case 3:
		for (i = 0; i < 5; i++) {
			do_anime(MAPVARS(gp).lv_gobj[i], i, 2);
		}
		MAPVARS(gp).xC4_b26 = 1;
		break;
	case 4:
		for (i = 0; i < 5; i++) {
			do_anime(MAPVARS(gp).lv_gobj[i], i, 3);
		}
		MAPVARS(gp).xC4_b26 = 1;
		break;
	case 5:
		for (i = 0; i < 5; i++) {
			do_anime(MAPVARS(gp).lv_gobj[i], i, 4);
		}
		MAPVARS(gp).xC4_b26 = 0;
		break;
	case 6:
		for (i = 0; i < 5; i++) {
			do_anime(MAPVARS(gp).lv_gobj[i], i, 5);
		}
		MAPVARS(gp).xC4_b26 = 1;
		break;
	case 7:
		for (i = 0; i < 5; i++) {
			do_anime(MAPVARS(gp).lv_gobj[i], i, 6);
		}
		MAPVARS(gp).xC4_b26 = 0;
		break;
	case 8:
		for (i = 0; i < 5; i++) {
			do_anime(MAPVARS(gp).lv_gobj[i], i, 7);
		}
		MAPVARS(gp).xC4_b26 = 1;
		break;
	case 9:
		for (i = 0; i < 5; i++) {
			do_anime(MAPVARS(gp).lv_gobj[i], i, 8);
		}

		temp_r28_10 = Stage_GetMapGObj(7)->userdata;
		JOBJ_GetWorldPosition(Stage_GetMapGObjJObj(Stage_GetMapGObj(7), 5), 0, &sp40);
		LASTVARS(temp_r28_10).xE0 = Stage_SpawnEffectPos(0x7531, 0x1E, &sp40);

		MAPVARS(gp).xC4_b26 = 0;
		break;
	case 10:
		grLast_8021C40C(gobj, grNLa_804DBBD4, 120.0F);
		grAnime_801C7A94(Stage_GetMapGObj(7), 5, 7, 0.0F);

		grlib_inline((MapData*)Stage_GetMapGObj(7)->userdata);

		MAPVARS(gp).xC4_b26 = 1;
		grLast_8021C6AC();
		break;
	case 11:
		for (i = 0; i < 5; i++) {
			do_anime(MAPVARS(gp).lv_gobj[i], i, 9);
		}
		MAPVARS(gp).xC4_b26 = 1;
		break;
	case 12:
		for (i = 0; i < 5; i++) {
			do_anime(MAPVARS(gp).lv_gobj[i], i, 10);
		}
		MAPVARS(gp).xC4_b26 = 0;
		break;
	case 13:
		grLast_8021C40C(gobj, grNLa_804DBBD8, 120.0F);
		for (i = 0; i < 5; i++) {
			Stage_ApplyColAnim(MAPVARS(gp).lv_gobj[i], grNLa_804D6AD0[0]);
			grMaterial_801C9698(MAPVARS(gp).lv_gobj[i]);
		}
		MAPVARS(gp).xC4_b26 = 1;
		break;
	case 14:
		grLast_8021C40C(gobj, (GXColor) { 0, 0, 0, 0 }, 60.0F);
		for (i = 0; i < 5; i++) {
			Stage_DestroyMapGObj(MAPVARS(gp).lv_gobj[i]);
			MAPVARS(gp).lv_gobj[i] = 0;
		}
		MAPVARS(gp).lv_gobj[5] = grLast_8021A7F4(grNLa_803E8010[5][0]);
		HSD_ASSERT(0x4D2, MAPVARS(gp).lv_gobj[5]);
		GObj_CopyGXPri(MAPVARS(gp).lv_gobj[5], gobj);
		do_anime(MAPVARS(gp).lv_gobj[5], 5, 0);
		Stage_ApplyColAnim(MAPVARS(gp).lv_gobj[5], grNLa_804D6AD0[1]);
		grMaterial_801C9698(MAPVARS(gp).lv_gobj[5]);
		Ground_801C1E00(0);
		MAPVARS(gp).xC4_b26 = 1;
		setBubbleColour();
		break;
	case 15:
		MAPVARS(gp).xC4_b26 = 0;
		break;
	case 16:
		grLast_8021C40C(gobj, (GXColor) { 0, 0, 0, 0 }, 60.0F);
		Stage_ApplyColAnim(MAPVARS(gp).lv_gobj[5], grNLa_804D6AD0[2]);
		grMaterial_801C9698(MAPVARS(gp).lv_gobj[5]);
		MAPVARS(gp).xC4_b26 = 1;
		break;
	case 17:
		for (i = 0; i < 5; i++) {
			MAPVARS(gp).lv_gobj[i] = grLast_8021A7F4(grNLa_803E8010[i][0]);
			HSD_ASSERT(0x4F0, MAPVARS(gp).lv_gobj[i]);
			GObj_CopyGXPri(MAPVARS(gp).lv_gobj[i], gobj);
			if (grNLa_803E8010[i][2] != -1) {
				Stage_SetMapJOBJAnim(MAPVARS(gp).lv_gobj[i], grNLa_803E8010[i][2], 7,
					grNLa_803E8010[i][3], 0.0F, 1.0F);
			}
			do_anime(MAPVARS(gp).lv_gobj[i], i, 0);
			Stage_ApplyColAnim(MAPVARS(gp).lv_gobj[i], grNLa_804D6AD0[3]);
			grMaterial_801C9698(MAPVARS(gp).lv_gobj[i]);
		}

		Stage_DestroyMapGObj(MAPVARS(gp).lv_gobj[5]);
		MAPVARS(gp).lv_gobj[5] = 0;
		Ground_801C1E00(1);
		MAPVARS(gp).xC4_b26 = 1;
		break;
	}
}

static int stageType_tracker;
static int frameCounter = 0;
#define FRAMES_TO_CHANGECOLOUR 2000
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
void debug_Stage_ColourShift(int x) {
	switch (x)
	{
	case NO_ERROR:
		OSReport("Success!\n");
		break;
	case FAILED_GET_DOBJ:
		OSReport("Failed to get dobj from jobj->dobj\n");
		break;
	case FAILED_GET_MOBJ:
		OSReport("Failed to get mobj from dobj->mobj\n");
		break;
	case FAILED_GET_MATERIAL:
		OSReport("Failed to get material from mobj->mat\n");
		break;
	}
}

#define STAGE_DOBJ_COUNT 2
static GXColor stage_targetColour[STAGE_DOBJ_COUNT];

void getAllDobjs_FromRootJobj(JOBJ* jobj,int* index, DOBJ* myDObjs[STAGE_DOBJ_COUNT]) {
	if (!jobj) return;

	// Process all DOBJs of current JOBJ;
	for (DOBJ* dobj = jobj->dobj; dobj; dobj = dobj->next) {
		if (*index >= STAGE_DOBJ_COUNT) return;
		myDObjs[*index] = dobj;
		(*index)++;
	}

	// Traverse children
	getAllDobjs_FromRootJobj(jobj->child, index, myDObjs);

	// Traverse siblings
	getAllDobjs_FromRootJobj(jobj->sibling, index, myDObjs);
}

void determineStageColour_BasedOnStageType(int stageType, GXColor stageColours[2]) {

	switch (stageType) {
	case BLUE:
		stageColours[0] = colourDefinitions[BLUE]; // Main surface
		stageColours[1] = colourDefinitions[WHITE]; // Frame
		break;
	case PURPLE:
		stageColours[0] = colourDefinitions[PURPLE];
		stageColours[1] = colourDefinitions[WHITE];
		break;
	case BLACK:
		stageColours[0] = colourDefinitions[BLACK];
		stageColours[1] = colourDefinitions[WHITE];
		break;
	case WHITE:
		stageColours[0] = colourDefinitions[WHITE];
		stageColours[1] = colourDefinitions[BLACK];
		break;
	case RED:
		stageColours[0] = colourDefinitions[RED];
		stageColours[1] = colourDefinitions[WHITE];
		break;
	default:
		stageColours[0] = colourDefinitions[BLACK];
		stageColours[1] = colourDefinitions[WHITE];
		break;
	}
}

#define STAGE_COLOURCHANGE_PERFRAME_CONSTANT 45

int stage_ColourChange(DOBJ* stageSurface, DOBJ* frame) {
	if (!stageSurface || !frame) return FAILED_GET_JOBJ;

	if (!stageSurface->mobj) return FAILED_GET_MOBJ;
	MOBJ* stageSurfaceMobj = stageSurface->mobj;
	if (!stageSurfaceMobj->mat) return FAILED_GET_MATERIAL;
	HSD_Material* stageSurfaceMat = stageSurfaceMobj->mat;
	if (stageSurfaceMat->diffuse.r != stage_targetColour[0].r || 
		stageSurfaceMat->diffuse.g != stage_targetColour[0].g ||
		stageSurfaceMat->diffuse.b != stage_targetColour[0].b)
	{
		stageSurfaceMat->diffuse.r += (stage_targetColour[0].r- stageSurfaceMat->diffuse.r)/STAGE_COLOURCHANGE_PERFRAME_CONSTANT;
		stageSurfaceMat->diffuse.g += (stage_targetColour[0].g - stageSurfaceMat->diffuse.g) / STAGE_COLOURCHANGE_PERFRAME_CONSTANT;
		stageSurfaceMat->diffuse.b += (stage_targetColour[0].b - stageSurfaceMat->diffuse.b) / STAGE_COLOURCHANGE_PERFRAME_CONSTANT;
	}

	if (!frame->mobj) return FAILED_GET_MOBJ;
	MOBJ* frameMobj = frame->mobj;
	if (!frameMobj->mat) return FAILED_GET_MATERIAL;
	HSD_Material* frameMat = frameMobj->mat;
	if (frameMat->diffuse.r != stage_targetColour[1].r ||
		frameMat->diffuse.g != stage_targetColour[1].g ||
		frameMat->diffuse.b != stage_targetColour[1].b)
	{
		frameMat->diffuse.r += (stage_targetColour[1].r - frameMat->diffuse.r) / STAGE_COLOURCHANGE_PERFRAME_CONSTANT;
		frameMat->diffuse.g += (stage_targetColour[1].g - frameMat->diffuse.g) / STAGE_COLOURCHANGE_PERFRAME_CONSTANT;
		frameMat->diffuse.b += (stage_targetColour[1].b - frameMat->diffuse.b) / STAGE_COLOURCHANGE_PERFRAME_CONSTANT;
	}

	return NO_ERROR; // No error
}

int stage_colourManager(GOBJ* gobj, int stageType) {
	if (!gobj || !gobj->hsd_object) return FAILED_GET_JOBJ;

	int myIndex = 0;
	DOBJ* myDobjs[STAGE_DOBJ_COUNT];
	getAllDobjs_FromRootJobj(gobj->hsd_object, &myIndex, myDobjs);

	determineStageColour_BasedOnStageType(stageType, stage_targetColour);

	int debug_colourChange = stage_ColourChange(myDobjs[0], myDobjs[1]);
	debug_Stage_ColourShift(debug_colourChange);
	return 0;
}

void toadAwsom_StageTransition(GOBJ* gobj, int mySwitch) {
	if (mySwitch == stageType_tracker) {
		mySwitch = (mySwitch + 1) % 5; // just change to next colour if same as current
	}
	switch (mySwitch) {
	case PURPLE:
		stageType_tracker = PURPLE;
		stage_colourManager(gobj, PURPLE);
		break;
	case BLUE:
		stageType_tracker = BLUE;
		stage_colourManager(gobj, BLUE);
		break;
	case BLACK:
		stageType_tracker = BLACK;
		stage_colourManager(gobj, BLACK);
		break;
	case RED:
		stageType_tracker = RED;
		stage_colourManager(gobj, RED);
		break;
	case WHITE:
		stageType_tracker = WHITE;
		stage_colourManager(gobj, WHITE);
		break;
	default:
		stageType_tracker = BLACK;
		stage_colourManager(gobj, BLACK);
		break;
	}
	
}

void onCreation_gobj3(GOBJ* gobj) {
	MapData* md = gobj->userdata;
	Stage_InitMovingColl(gobj->hsd_object, md->index);
	Stage_MapStateChange(gobj, md->index, 0);
	MAPVARS(md).unk2_stageEffect_var = true;
	for (int i = 0; i < ARRAY_SIZE(MAPVARS(md).lv_gobj); i++) {
		MAPVARS(md).lv_gobj[i] = 0;
	}
	MAPVARS(md).MAIN_SWITCH = 0;
	MAPVARS(md).xC4_b26 = false;
	MAPVARS(md).xC4_b27 = true;

	transition_machine(gobj, 1);

	int rand = HSD_Randi(3);
	int debug_ColourShift_result;
	OSReport("Rand result %d\n", rand);
	toadAwsom_StageTransition(gobj, rand);

	MAPVARS(md).unk_stageEffect_var = 0;
	void* (*goCb)(GOBJ*) = (void*)0x8021A9AC;
	Match_StoreGoCallback(gobj, goCb);
}

void onDeletion_gobj3(GOBJ* gobj) { return 0; }

void onframe_gobj3(GOBJ* gobj) {
	MapData* gp = gobj->userdata;
	stage_colourManager(gobj, stageType_tracker);
	frameCounter++;
	if(frameCounter > FRAMES_TO_CHANGECOLOUR) {
		frameCounter = 0;
		int rand = HSD_Randi(3);
		OSReport("Changing colour to %d\n", rand);
		toadAwsom_StageTransition(gobj, rand);
	}

	if (!(MAPVARS(gp).unk_stageEffect_var) && !(MAPVARS(gp).unk2_stageEffect_var)) {
		stageEffectsAndVars(gobj);
		if (MAPVARS(gp).xC4_b26 != 0) {
			int tmp = state_machine(gobj); ///NOT CHUNGUS
			//OSReport("state: %d\n", tmp);
			if (tmp != 0) {
				//transition_machine(gobj, tmp); //chungus
			}
		}
	}
	Stage_UpdateMovingColl(gobj);
	Dynamics_DecayWind();
}

////////////////
// gobj 4 cbs //
////////////////

void onCreation_gobj4(GOBJ* gobj) {
	MapData* md = gobj->userdata;
	Stage_InitColAnim(gobj->hsd_object);
	md->render_kind = 2;
	Stage_SetMapJOBJAnim(gobj, gobj->hsd_object, 7, 10, 0, 1);
}
void onDeletion_gobj4(GOBJ* gobj) { return 0; }
void onframe_gobj4(GOBJ* gobj) {}

void newOnCreation_gobj4(GOBJ* gobj) {
	MapData* md = gobj->userdata;
	Stage_InitColAnim(gobj->hsd_object);
	md->render_kind = 2;
}
//////////////////
// white bg cbs //
//////////////////
void onCreation_whiteBg(GOBJ* gobj) {
	MapData* md = gobj->userdata;
	Stage_InitColAnim(gobj->hsd_object);
	md->render_kind = 1;
	Stage_MapStateChange(gobj, md->index, 9);
	Stage_SetMapJOBJAnim(gobj, gobj->hsd_object, 0, 9, 0, 1);
}
void onDeletion_whiteBg(GOBJ* gobj) { return 0; }
void onframe_whitebg(GOBJ* gobj) {

	if (Stage_CheckAnimEnd(gobj, gobj->hsd_object, 0x2) != 0) {
		OSReport("white bg end anim doing...\n");
		Stage_SetMapJOBJAnim(gobj, gobj->hsd_object, 0x2, 10, 0, 1);
	}
}


//////////////
// Map init //
//////////////
static GOBJ* grLast_8021A7F4(int id) //create gobj?
{
	GOBJ* gobj;
	MapData* gp;
	MapDesc* cb;

	cb = &map_gobjs[id]; // MapDescPointer = 803E7EBC, This must get the callbacks for the gobj given
	GOBJ* (*Ground_801C14D0)(int) = (void*)0x801C14D0; // GetGObjByID?
	gobj = Ground_801C14D0(id);
	if (gobj != 0) {
		gp = gobj->userdata;
		gp->post_anim_cb = 0;
		gp->xC = 0;
		GObj_AddGXLink(gobj, GXLink_Stage, 3, 0);
		if (cb->onDeletion != 0) {
			gp->post_anim_cb = cb->onDeletion;
		}
		if (cb->onCreation != 0) {
			cb->onCreation(gobj);
		}
		if (cb->onFrame != 0) {
			GObj_AddProc(gobj, cb->onFrame, 4);
		}
	}
	else {
		OSReport("%s:%d: couldn t get gobj(id=%d)\n", __FILE__, 255, id);
	}
	return gobj;
}
void oninit(GOBJ* gobj) {
	Stage* stage = STAGE_INFO_ADDR;
	grNLa_804D6AD0 = stage->yakumono_param;
	stage->flags2x08 = 1;
	stage->flags2x04 = 1;
	grLast_8021A7F4(0);
	grLast_8021A7F4(1);
	grLast_8021A7F4(2);
	grLast_8021A7F4(3);
	GOBJ* gobj8 = grLast_8021A7F4(8);
	void* (*someCameraCb)() = (void*)0x801C39C0;
	someCameraCb();
	void* (*someBlastzoneCb)() = (void*)0x801C3BB4;
	someBlastzoneCb();
	Match_SetNearClip(1);
	Match_SetFarClip(30000);
	MapData* md8 = gobj8->userdata;
	Stage_MapStateChange(gobj8, md8->index, 10);
}

static MapDesc map_gobjs[] = {
	// map gobj 0
	{
		.onCreation = 0x8021A8E0,
		.onDeletion = 0x8021A90C,
		.onFrame = 0x8021A914,
		.onUnk = 0x8021A918,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 1
	{
		.onCreation = 0x8021A91C,
		.onDeletion = 0x8021A960,
		.onFrame = 0x8021A968,
		.onUnk = 0x8021A96C,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 2
	{
		.onCreation = 0x8021A970,
		.onDeletion = 0x8021A99C,
		.onFrame = 0x8021A9A4,
		.onUnk = 0x8021A9A8,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 3
	{
		.onCreation = onCreation_gobj3,
		.onDeletion = 0x8021AAA8,
		.onFrame = onframe_gobj3,
		.onUnk = 0x8021AB30,
		.is_lobj = 1,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 4
	{
		.onCreation = 0x8021AB34,
		.onDeletion = 0x8021AB78,
		.onFrame = 0x8021AB80,
		.onUnk = 0x8021AB84,
		.is_lobj = 0,
		.is_fog = 1,
		.is_cobj = 0,
	},
	// map gobj 5
	{
		.onCreation = 0x8021AB88,
		.onDeletion = 0x8021ABCC,
		.onFrame = 0x8021ABD4,
		.onUnk = 0x8021ABD8,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 6
	{
		.onCreation = 0x8021ABDC,
		.onDeletion = 0x8021AC20,
		.onFrame = 0x8021AC28,
		.onUnk = 0x8021AC2C,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 7
	{
		.onCreation = 0x8021AC30,
		.onDeletion = 0x8021ADC8,
		.onFrame = 0x8021ADD0,
		.onUnk = 0x8021B23C,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 8
	{
		.onCreation = 0x8021B240,
		.onDeletion = 0x8021B284,
		.onFrame = 0x8021B28C,
		.onUnk = 0x8021B290,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 9
	{
		.onCreation = 0x8021B294,
		.onDeletion = 0x8021B2D8,
		.onFrame = 0x8021B2E0,
		.onUnk = 0x8021B2E4,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
};
