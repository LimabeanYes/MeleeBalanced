#ifndef GR_WARIOS_CASTLE_H
#define GR_WARIOS_CASTLE_H

#include <mex.h>

#define NUM_PAINTINGS 3

enum StageSFX
{
    SFX_SPLASH,
    SFX_UNK_WATER,
    SFX_BIG_SPLASH,
    SFX_RIVER
};

enum MapParts
{
    MAP_COLLISION,
    MAP_BG,
    MAP_WHISPY,
    MAP_GROUND,
};

enum LineGroups
{
    LG_MAINSTAGE
};

typedef struct GrParam
{
    int num_paintings;
} GrParam;

typedef struct StageGrData
{
    GOBJ* painting;
} StageGrData;

typedef struct PaintingGrData
{
    int rand;
} PaintingGrData;

int CheckForSplash(GOBJ*, GOBJ*);
#endif