#include "mex.h"


#define METER_FILENAME "Meters.dat"
#define METER_SYMBOL "Relax_scene_models"
#define FRAMES_UNTIL_METERFULL 1500

enum specialStates {
    asid_SpecialLwAlt = 367,
	asid_SpecialAirLwAlt
};

typedef struct ftPichu_FighterVars {
    int filler0[48];
	float framecounter;
    int flag_meterMode;
}ftPichu_FighterVars;

typedef struct Symbol_WpInd_scene_models
{
    JOBJSet* WpInd_scene_models;
} Symbol_WpInd_scene_models;

typedef struct MeterVars
{
    GOBJ* fighter;
    int* ply;
    int state;
    int framesleft;
    Vec3 stoppos[4];
    Vec3 kb[4];
    int framecounter;
} MeterVars;