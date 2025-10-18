#ifndef FT_TOAD_H
#define FT_TOAD_H

#include "mex.h"

#define IS_DEBUG 4
#define DEBUG_TOADAWSOM_CONSTANT 101250000 * 10

#define METER_FILENAME "Meters.dat"
#define METER_SYMBOL "Relax_scene_models"
///////////////////////
//      m-ex IDs     //
///////////////////////

#define MEX_ITEM_ICEBALL 0

#define MEX_EFFECT_FIREBALL 5000
#define MEX_EFFECT_DSPECIAL 5001

#define MEX_SOUND_FIREBALL_DESTROY 5025



#define VANILLA_SOUND_FIREBALL_DESTROY 180025

///////////////////////
//  Special States   //
///////////////////////

#define STATE_SPECIALN 343
#define STATE_SPECIALNAIR 344
#define STATE_SPECIALS 345
#define STATE_SPECIALSAIR 346
#define STATE_SPECIALHI 347
#define STATE_SPECIALHIAIR 348
#define STATE_SPECIALLW 349
#define STATE_SPECIALLWAIR 350

///////////////////////
//    Item States    //
///////////////////////

#define STATE_FIREBALL 0
#define STATE_SHELL 0

///////////////////////
//      Structs      //
///////////////////////

#define SHELL_TIME 240
#define SHELL_DMG 4
#define SHELL_BOUNCEBACK_VEL 0.9
#define SHELL_BOUNCE_VEL 0.366
#define SHELL_LIFETIME_ADD 10
#define MIN_SHELL_VEL 0.6
#define MAX_SHELL_VEL 1.5
#define SHELL_GRAV 0.15
#define SHELL_MAXFALL 2.2

#define STANCE_MAX 3
#define DASHRUN_TERMINAL_VELOCITY 1.3
#define GROUND_FRICTION 0.045
#define DASH_INITIAL_VELOCITY 0.9
#define WEIGHT 100
#define HOP_V_INITIAL_VELOCITY 2.66
#define AERIAL_DRIFT_MAX 0.65

typedef struct ToadPrimaryAttributes {
    float dashrun_terminal_velocity;
    float ground_friction;
    float dash_initial_velocity;
    float weight;
    float hop_v_initial_velocity;
    float aerial_drift_max;
	float aerial_friction;
}ToadPrimaryAttributes;

typedef struct ToadAttr
{
    float specialS_base_air_speed;            //x00
    float specialS_x_vel_clamp;               //x04
    float specialS_x_accel;                   //x08
    float specialS_x_drift;                   //x0C
    float specialS_rising_tap_power;          //x10
    float specialS_terminal_velocity;         //x14 (replacing int, im not sure if Im allowed to do that)
    float specialHi_fall_air_mobility;        //x18
    float specialHi_landing_lag;              //x1C
    float specialHi_stick_reverse_threshold;  //x20
    float specialHi_stick_threshold;          //x24
    float specialHi_stick_control;            //x28
    float specialHi_initial_x_momemtum;       //x2C
    float specialHi_initial_gravity;          //x30
    float specialHi_initial_y_momemtum;       //x34
    float specialLw_grounded_rise_resistance; //x38             -hardcode to 0.6
    float specialLw_base_air_speed;           //x3C             -Necessary
    float specialLw_x_vel_clamp;              //x40             -Necessary
    float specialLw_x_accel;                  //x44 (?)         -Necessary
    float specialLw_x_drift;                  //x48             -Necessary  
    float speicalLw_air_speed_decel;          //x4C             -hardcode to 0.83
    float specialLw_rise_constant;            //x50;            -hardcode to 4
    float specialLw_rising_tap_power;         //x54             -Necessary
    float specialLw_terminal_velocity;        //x586            -Necessary
    int specialLw_freefall_toggle;            //x5C             -hardcode to 0... or just remove from code?
    float specialLw_upward_decay;              //0x60
    float specialLw_landing_lag;               //0x64
    float specialLw_downward_decay;            //0x68
    float specialLw_clamp_speedDown            //0x6c
} ToadAttr;

typedef struct ToadCharVar
{
    int var1;
    int var2;
    int var3;
    int var4;
    int var6;
    int stance;
    int stance_framesRemaining;
    GOBJ* meterGobj;
} ToadCharVar;

typedef struct IceballAttr
{
    float speed;
    float angle;
    float life;
    float unk1;
    float max_speed;
} IceballAttr;

typedef struct ShellAttr
{
    float unk1; //0x0
    float unk2; //0x4
    float lifetime; //0x8
    float unk4; //0xc
    float unk5;//0x10
    float unk6; //0x14
    float unk7; //0x18
    float unk8; //0x1c
    float unk9; // 0x20
    float unk10; //0x24
    float unk11; //0x28
    float unk12; //0x2c
    float unk13; //0x30
    float unk14; //0x34
    float unk15; //0x38
    float unk16; //0x3c
} ShellAttr;


typedef struct SpecialLwFtCmd
{
    int interruptable;
} SpecialLwFtCmd;

typedef struct SpecialSFtCmd
{
    int decay_air_speed;
    int disable_rise; 		//?
} SpecialSFtCmd;

typedef struct SpecialSVar
{
    float air_speed;	// x00
    int x04;			// x04
    int x08;			// x08
    float on_ground;	// x0C
} SpecialSVar;


typedef struct SpecialHiFtCmd
{
    int can_control;
} SpecialHiFtCmd;

typedef struct Symbol_WpInd_scene_models
{
    JOBJSet* WpInd_scene_models;
} Symbol_WpInd_scene_models;


typedef struct SpecialLwVar
{
    float air_speed;	// x00
    float riseSpeed;	// x04
    int x08;			// x08
    float on_ground;	// x0C
} SpecialLwVar;


typedef struct MeterVars
{
    GOBJ* fighter;
    int* ply;
    int state;
    int framesleft;
    Vec3 stoppos[4];
    Vec3 kb[4];
} MeterVars;


///////////////////////
//     Functions     //
///////////////////////

// 0xc4c508c
#define SPECIALS_TRANSITION_FLAGS (FIGHTER_GFX_PRESERVE | FIGHTER_HITSTATUS_COLANIM_PRESERVE | FIGHTER_MODEL_NOUPDATE | FIGHTER_ANIMVEL_NOUPDATE | FIGHTER_UNK_0x40 | FIGHTER_MATANIM_NOUPDATE | FIGHTER_THROW_EXCEPTION_NOUPDATE | FIGHTER_SFX_PRESERVE | FIGHTER_PARASOL_NOUPDATE)

// Think
void FireBallThink(GOBJ*);

void setupMeter_debug(int debugMessage);
void printAttrs_debug(FighterData* fd, char* calledBy);
void CheckConst_debug();

GOBJ* setupMeter(GOBJ* gobj);
void meterLogic(GOBJ* gobj);

// Special N
void SpecialN_AnimationCallback(GOBJ* gobj);
void SpecialN_IASACallback(GOBJ* gobj);
void SpecialN_PhysicCallback(GOBJ* gobj);
void SpecialN_CollisionCallback(GOBJ* gobj);

void SpecialAirN_AnimationCallback(GOBJ* gobj);
void SpecialAirN_IASACallback(GOBJ* gobj);
void SpecialAirN_PhysicCallback(GOBJ* gobj);
void SpecialAirN_CollisionCallback(GOBJ* gobj);

// SpecialS
void SpecialS_AnimationCallback(GOBJ* gobj);
void SpecialS_IASACallback(GOBJ* gobj);
void SpecialS_PhysicCallback(GOBJ* gobj);
void SpecialS_CollisionCallback(GOBJ* gobj);

void SpecialAirS_AnimationCallback(GOBJ* gobj);
void SpecialAirS_IASACallback(GOBJ* gobj);
void SpecialAirS_PhysicCallback(GOBJ* gobj);
void SpecialAirS_CollisionCallback(GOBJ* gobj);

// Specialhi
void SpecialHi_AnimationCallback(GOBJ* gobj);
void SpecialHi_IASACallback(GOBJ* gobj);
void SpecialHi_PhysicCallback(GOBJ* gobj);
void SpecialHi_CollisionCallback(GOBJ* gobj);

void SpecialAirHi_AnimationCallback(GOBJ* gobj);
void SpecialAirHi_IASACallback(GOBJ* gobj);
void SpecialAirHi_PhysicCallback(GOBJ* gobj);
void SpecialAirHi_CollisionCallback(GOBJ* gobj);

// SpecialLw
void SpecialLw_AnimationCallback(GOBJ* gobj);
void SpecialLw_IASACallback(GOBJ* gobj);
void SpecialLw_PhysicCallback(GOBJ* gobj);
void SpecialLw_CollisionCallback(GOBJ* gobj);

void SpecialAirLw_AnimationCallback(GOBJ* gobj);
void SpecialAirLw_IASACallback(GOBJ* gobj);
void SpecialAirLw_PhysicCallback(GOBJ* gobj);
void SpecialAirLw_CollisionCallback(GOBJ* gobj);

void SpecialN_SpawnFireballThink(GOBJ* gobj);
void stanceUp(GOBJ* gobj);
// #define bool u8
// #define true 1
// #define false 0
#include <stdbool.h>

/// @brief checks item collision with any line and applies bounce physics if it touches any
/// @param item
/// @return TRUE if collision was made and FALSE otherwise
bool (*Item_Coll_Bounce)(GOBJ* item) = (int*)0x8027781c;

/// @brief removes all references to specificed fighter from item
/// @param item
/// @param fighter
/// @return TRUE if fighter reference was removed and FALSE otherwise
//bool (*Item_RemoveFighterReference)(GOBJ *item, GOBJ *fighter) = (int *)0x8026b894;

/// @brief updates item flags related to hitlag TODO: better description
/// @param item
//void (*Item_ClearHitlagFlag)(GOBJ *item) = (void *)0x8026b73c;

/// @brief 
/// @param item 
/// @return 
inline void* Item_GetItCmdFlags(GOBJ* item)
{
    return &((ItemData*)item->userdata)->itcmd_var;
}

/// @brief 
/// @param item 
/// @return 
inline void* Item_GetItemVar(GOBJ* item)
{
    return &((ItemData*)item->userdata)->item_var;
}

/// @brief Fighter Variables are used globally by the fighter
/// @param fighter GOBJ of Fighter
/// @return pointer to Fighter's "Fighter Variable" struct
inline void* Fighter_GetFighterVars(GOBJ* fighter)
{
    return &((FighterData*)fighter->userdata)->fighter_var;
}

inline void* Fighter_GetStateVars(GOBJ* fighter)
{
    return &((FighterData*)fighter->userdata)->state_var;
}

inline void* Fighter_GetScriptVars(GOBJ* fighter)
{
    return &((FighterData*)fighter->userdata)->ftcmd_var;
}

inline void* Fighter_GetSpecialAttributes(GOBJ* fighter)
{
    return ((FighterData*)fighter->userdata)->special_attributes;
}

#endif