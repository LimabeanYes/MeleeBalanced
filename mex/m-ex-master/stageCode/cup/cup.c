#include "cup.h"

void oninit(GOBJ* gobj) {
	Stage* stage = STAGE_INFO_ADDR;
	grNLa_804D6AD0 = stage->yakumono_param;
	stage->flags2x08 = 1;
	stage->flags2x04 = 1;
	void* (*grLast_8021A7F4)(int) = (void*)0x8021A7F4;
	grLast_8021A7F4(0);
	grLast_8021A7F4(1);
	grLast_8021A7F4(2);
	grLast_8021A7F4(3);
	void* (*someCameraCb)() = (void*)0x801C39C0;
	someCameraCb();
	void* (*someBlastzoneCb)() = (void*)0x801C3BB4;
	someBlastzoneCb();
	Match_SetNearClip(1);
	Match_SetFarClip(30000);
}

void debug_Stage_ColourShift(int x) {
	switch (x)
	{
	case NO_ERROR:
		//OSReport("Success!\n");
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

void getAllDobjs_FromRootJobj(JOBJ* jobj, int* index, DOBJ* myDObjs[STAGE_DOBJ_COUNT]) {
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
		stageSurfaceMat->diffuse.r += (stage_targetColour[0].r - stageSurfaceMat->diffuse.r) / STAGE_COLOURCHANGE_PERFRAME_CONSTANT;
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

	void* (*transition_machine)(GOBJ*, int) = (void*)0x8021B920;
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
	if (frameCounter > FRAMES_TO_CHANGECOLOUR) {
		frameCounter = 0;
		int rand = HSD_Randi(3);
		OSReport("Changing colour to %d\n", rand);
		toadAwsom_StageTransition(gobj, rand);
	}
	Stage_UpdateMovingColl(gobj);
	Dynamics_DecayWind();
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
