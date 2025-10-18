#include "grgr.h"
#include <mex.h>

////////////////////
// General Points //
////////////////////
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

////////////////
// Background //
////////////////
void Background_OnCreation(GOBJ* map)
{
    MapData* map_data = map->userdata;

    Stage_MapStateChange(map, map_data->index, 0);

    // unk gx priority
    // map_data->gx_unk2 = 2;

    // disable fog
    map_data->is_fog = 0;

    // no zupdate and zmode always
    // JOBJ_SetAllMOBJFlags(map->hsd_object, RENDER_ZMODE_ALWAYS | RENDER_NO_ZUPDATE);

    return;
}
int Background_OnDeletion(GOBJ* map)
{
    return 0;
}
void Background_OnFrame(GOBJ* map)
{
    return;
}
void Background_OnUnk(GOBJ* map)
{
    return;
}



////////////////
// Main Stage //
////////////////
void Stage_OnCreation(GOBJ* map)
{
    MapData* map_data = map->userdata;

    Stage_MapStateChange(map, map_data->index, 0);

    Stage_InitMovingColl(map->hsd_object, map_data->index);

    Stage_EnableLineGroup(LG_MAINSTAGE); // main

    return;
}
int Stage_OnDeletion(GOBJ* map)
{
    return 0;
}
void Stage_OnFrame(GOBJ* map)
{
    return;
}
void Stage_OnUnk(GOBJ* map)
{
    return;
}

void BG_OnCreation(GOBJ* map)
{
    MapData* map_data = map->userdata;
    StageGrData* data = &map_data->map_var;

    Stage_MapStateChange(map, map_data->index, 0);

    Stage_InitMovingColl(map->hsd_object, map_data->index);

    return;
}
int BG_OnDeletion(GOBJ* map)
{
    return 0;
}
void BG_OnFrame(GOBJ* map)
{
    return;
}
void BG_OnUnk(GOBJ* map)
{
    return;
}

//////////////
//Map States//
//////////////
__attribute__((used))
static struct MapDesc map_gobjs[] = {
	// map gobj 0
	{
		.onCreation = 0x8021360C,
		.onDeletion = 0x802138AC,
		.onFrame = 0x802138B4,
		.onUnk = 0x802138B8,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 2
	{
		.onCreation = 0x802138BC,
		.onDeletion = 0x80213900,
		.onFrame = 0x80213908,
		.onUnk = 0x8021390C,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 5
	{
		.onCreation = 0x802139C4,
		.onDeletion = 0x80213AAC,
		.onFrame = 0x80213C10,
		.onUnk = 0x80214654,
		.is_lobj = 0,
		.is_fog = 0,
		.is_cobj = 0,
	},
	// map gobj 6
	{
		.onCreation = 0x80214674,
		.onDeletion = 0x80214794,
		.onFrame = 0x8021479C,
		.onUnk = 0x80214804,
		.is_lobj = 1,
		.is_fog = 1,
		.is_cobj = 0,
	},
    {
        .onCreation = 0x0,
        .onDeletion = 0x0,
        .onFrame = 0x0,
        .onUnk = 0x0,
        .is_lobj = 1,
        .is_fog = 1,
        .is_cobj = 0,
    },
    {
        .onCreation = 0x0,
        .onDeletion = 0x0,
        .onFrame = 0x0,
        .onUnk = 0x0,
        .is_lobj = 1,
        .is_fog = 1,
        .is_cobj = 0,
    },
};

////////
//Main//
////////
/*
void OnInit()
{
    // create map gobjs
    Stage_CreateMapGObj(MAP_COLLISION);
    Stage_CreateMapGObj(MAP_BG);
    Stage_CreateMapGObj(MAP_WHISPY);
    Stage_CreateMapGObj(MAP_GROUND);

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
*/