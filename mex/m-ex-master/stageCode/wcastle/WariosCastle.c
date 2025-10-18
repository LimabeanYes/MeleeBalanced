#include "./WariosCastle.h"
#include <mex.h>

static struct GrParam *gr_param;

__attribute__((used)) 
static struct GrParam yakumono_param = {
    .num_paintings = 3
};

////////////////////
// General Points //
////////////////////
void Points_OnCreation(GOBJ *map)
{
    MapData *md = map->userdata;
    Stage_MapStateChange(map, md->index, 0);
    return;
}
int Points_OnDeletion(GOBJ *map)
{
    return 0;
}
void Points_OnFrame(GOBJ *map)
{
    return;
}
void Points_OnUnk(GOBJ *map)
{
    return;
}

////////////////
// Background //
////////////////
void Background_OnCreation(GOBJ *map)
{
    MapData *map_data = map->userdata;

    Stage_MapStateChange(map, map_data->index, 0);

    // unk gx priority
    // map_data->gx_unk2 = 2;

    // disable fog
    map_data->is_fog = 0;

    // no zupdate and zmode always
    // JOBJ_SetAllMOBJFlags(map->hsd_object, RENDER_ZMODE_ALWAYS | RENDER_NO_ZUPDATE);

    return;
}
int Background_OnDeletion(GOBJ *map)
{
    return 0;
}
void Background_OnFrame(GOBJ *map)
{
    return;
}
void Background_OnUnk(GOBJ *map)
{
    return;
}

// This is the callback to see if a fighter hits the water
int CheckForSplash(GOBJ* stage, GOBJ* fighter)
{
    if (fighter)
    {
        FighterData *fd = fighter->userdata;

        float position = -25.0f;

        if (fd && fd->phys.pos.Y < position && fd->phys.pos_prev.Y > position) 
        {
            Vec3 effect_spawn_pos = 
            { 
                fd->phys.pos.X, 
                position, 
                fd->phys.pos.Z 
            };

            float particle_scale = fd->camera_subject->x50 / 15;
            
            ptclGen *effect = Stage_SpawnEffectPos(30000, 30, &effect_spawn_pos);

            if (effect != 0) 
            {
                // Changes to appsrt in later versions of m-ex
                GeneratorAppSRT *srt = effect->appsrt;
                srt->scale.X *= particle_scale;
                srt->scale.Y *= particle_scale;
                srt->scale.Z *= particle_scale;
            }

            // play splash sfx
            SFX_PlayStageSFX(SFX_BIG_SPLASH);
        }
    }

    return 0;
}

// Water
void Water_OnCreation(GOBJ *map)
{
    MapData *map_data = map->userdata;

    Stage_MapStateChange(map, map_data->index, 0);

    // unk gx priority
    // map_data->gx_unk2 = 2;
    Stage_AddFtChkDevice(map, 6, CheckForSplash);

    // disable fog
    map_data->is_fog = 0;

    // start the river sfx
    SFX_PlayStageSFX(SFX_RIVER);

    return;
}
int Water_OnDeletion(GOBJ *map)
{
    return 0;
}
void Water_OnFrame(GOBJ *map)
{
    return;
}
void Water_OnUnk(GOBJ *map)
{
    return;
}

//////////////
// Painting //
//////////////
int GetPaintingID()
{
    int rand = HSD_Randi(100);

    if(rand <= 0) // Special Painting (Secret, 1%)
    {
        return 1;
    }
    else if(rand <= 10) // Unknown as of writing (Rare, ~10%)
    {
        return 4;
    }
    else if(rand <= 30) // Unknown as of writing (Uncommon, ~20%)
    {
        return 3;
    }
    else // Main Wario painting (Common, ~70%)
    {
        return 2;
    }
}

void Painting_OnCreation(GOBJ *map)
{
    MapData *map_data = map->userdata;
    PaintingGrData *data = &map_data->map_var;

    // Get the index here --> 0 is the last spot I fucking hate this
    data->rand = GetPaintingID();
    //data->rand = HSD_Randi(4) + 1;

    Stage_MapStateChange(map, map_data->index, 0);

    // get jobj of the painting
    JOBJ* painting_jobj = Stage_GetMapGObjJObj(map, 0);
    JOBJ_SetAnimFrame(painting_jobj, data->rand * 1.0f);
    return;
}
int Painting_OnDeletion(GOBJ *map)
{
    return 0;
}
void Painting_OnFrame(GOBJ *map)
{
    MapData *map_data = map->userdata;
    PaintingGrData *data = &map_data->map_var;

    JOBJ* painting_jobj = Stage_GetMapGObjJObj(map, 0);
    JOBJ_SetAnimFrame(painting_jobj, data->rand * 1.0f);
    return;
}
void Painting_OnUnk(GOBJ *map)
{
    return;
}

////////////////
// Main Stage //
////////////////
void Stage_OnCreation(GOBJ *map)
{
    MapData *map_data = map->userdata;

    Stage_MapStateChange(map, map_data->index, 0);

    Stage_InitMovingColl(map->hsd_object, map_data->index);

    Stage_EnableLineGroup(LG_MAINSTAGE); // main

    return;
}
int Stage_OnDeletion(GOBJ *map)
{
    return 0;
}
void Stage_OnFrame(GOBJ *map)
{
    return;
}
void Stage_OnUnk(GOBJ *map)
{
    return;
}

void BG_OnCreation(GOBJ *map)
{
    MapData *map_data = map->userdata;
    StageGrData *data = &map_data->map_var;

    Stage_MapStateChange(map, map_data->index, 0);

    Stage_InitMovingColl(map->hsd_object, map_data->index);

    return;
}
int BG_OnDeletion(GOBJ *map)
{
    return 0;
}
void BG_OnFrame(GOBJ *map)
{
    return;
}
void BG_OnUnk(GOBJ *map)
{
    return;
}

//////////////
//Map States//
//////////////
__attribute__((used)) static MapDesc map_gobjs[] = {
    // Collision
    {
        .onCreation = Points_OnCreation,
        .onDeletion = Points_OnDeletion,
        .onFrame = Points_OnFrame,
        .onUnk = Points_OnUnk,
        .is_lobj = 0,
        .is_fog = 0,
        .is_cobj = 0,
    },
    // Background - Water
    {
        .onCreation = Water_OnCreation,
        .onDeletion = Water_OnDeletion,
        .onFrame = Water_OnFrame,
        .onUnk = Water_OnUnk,
        .is_lobj = 0, 
        .is_fog = 0,
        .is_cobj = 0,
    },
    // Background - Floating Objects
    {
        .onCreation = Background_OnCreation,
        .onDeletion = Background_OnDeletion,
        .onFrame = Background_OnFrame,
        .onUnk = Background_OnUnk,
        .is_lobj = 0, 
        .is_fog = 0,
        .is_cobj = 0,
    },
    // Background - Main Background
    {
        .onCreation = BG_OnCreation,
        .onDeletion = BG_OnDeletion,
        .onFrame = BG_OnFrame,
        .onUnk = BG_OnUnk,
        .is_lobj = 0, // Uhhhh
        .is_fog = 0, // Uhhhh
        .is_cobj = 0,
    },
    // Background - Painting
    {
        .onCreation = Painting_OnCreation,
        .onDeletion = Painting_OnDeletion,
        .onFrame = Painting_OnFrame,
        .onUnk = Painting_OnUnk,
        .is_lobj = 0, // Uhhhh
        .is_fog = 0, // Uhhhh
        .is_cobj = 0,
    },
    // Main Platform - Mushroom
    {
        .onCreation = Stage_OnCreation,
        .onDeletion = Stage_OnDeletion,
        .onFrame = Stage_OnFrame,
        .onUnk = Stage_OnUnk,
        .is_lobj = 1, // Uhhhh
        .is_fog = 1, // Uhhhh
        .is_cobj = 0,
    },
};

////////
//Main//
////////
void OnInit()
{
    // get yakumono (Stage parameters)
    gr_param = Stage_GetYakumonoParam();

    if (gr_param == 0)
        __assert("WariosCastle.c", __LINE__, "yakumono node not found");

    // create map gobjs
    Stage_CreateMapGObj(MAP_COLLISION);
    Stage_CreateMapGObj(MAP_WATER);
    Stage_CreateMapGObj(MAP_FLOATINGOBJECTS);
    Stage_CreateMapGObj(MAP_BACKGROUND);
    Stage_CreateMapGObj(MAP_PAINTING);
    Stage_CreateMapGObj(MAP_STAGE);

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
void *onTouchLine(int line_id)
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
