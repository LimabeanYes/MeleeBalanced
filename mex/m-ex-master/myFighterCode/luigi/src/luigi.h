#ifndef FT_LUIGI_H
#define FT_LUIGI_H

#include "mex.h"

#define FIREBALL_LANDING_LAG 12

#define S_LAND_LAG 16
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
//    Vanilla IDs    //
///////////////////////

#define VANILLA_ITEM_FIREBALL 0x30
//#define VANILLA_ITEM_CAPE (item id is defined in Mario's special attributes)

#define VANILLA_EFFECT_FIREBALL 1146
#define VANILLA_EFFECT_FIREBALL_FLAME 1147
#define VANILLA_EFFECT_DSPECIAL 1148
#define VANILLA_EFFECT_CAPE1 1149
#define VANILLA_EFFECT_CAPE2 1150

#define VANILLA_SOUND_FIREBALL_DESTROY 180025
///////////////////////
//    Item States    //
///////////////////////

#define STATE_FIREBALL 0

///////////////////////
//      Structs      //
///////////////////////

#define gravChanger 1.5

typedef struct LuigiAttr
{
    /// SIDE SPECIAL - GREEN MISSILE
    float x0_LUIGI_GREENMISSILE_UNK1;
    float x4_LUIGI_GREENMISSILE_SMASH;
    float x8_LUIGI_GREENMISSILE_CHARGE_RATE;
    float xC_LUIGI_GREENMISSILE_MAX_CHARGE_FRAMES;
    float x10_LUIGI_GREENMISSILE_DAMAGE_TILT;
    /// (base damage + charge duration) * this value?
    float x14_LUIGI_GREENMISSILE_DAMAGE_SLOPE;
    float x18_LUIGI_GREENMISSILE_TRACTION;
    float x1C_LUIGI_GREENMISSILE_UNK2;
    float x20_LUIGI_GREENMISSILE_FALLING_SPEED;
    float x24_LUIGI_GREENMISSILE_VEL_X;
    float x28_LUIGI_GREENMISSILE_MUL_X;
    float x2C_LUIGI_GREENMISSILE_VEL_Y;
    float x30_LUIGI_GREENMISSILE_MUL_Y;
    float x34_LUIGI_GREENMISSILE_GRAVITY_START;
    float x38_LUIGI_GREENMISSILE_FRICTION_END;
    float x3C_LUIGI_GREENMISSILE_X_DECEL;
    float x40_LUIGI_GREENMISSILE_GRAVITY_MUL;
    /// 1.0f divided by this value
    float x44_LUIGI_GREENMISSILE_MISFIRE_CHANCE;
    float x48_LUIGI_GREENMISSILE_MISFIRE_VEL_X;
    float x4C_LUIGI_GREENMISSILE_MISFIRE_VEL_Y;
    /// UP SPECIAL - SUPER JUMP PUNCH
    /// Multiplies Luigi's max horionztal aerial mobility
    float x50_LUIGI_SUPERJUMP_FREEFALL_MOBILITY;
    float x54_LUIGI_SUPERJUMP_LANDING_LAG;
    /// Minimum stick range required for turnaround
    float x58_LUIGI_SUPERJUMP_REVERSE_STICK_RANGE;
    /// Minimum stick range required for horionztal momentum?
    float x5C_LUIGI_SUPERJUMP_MOMENTUM_STICK_RANGE;
    float x60_LUIGI_SUPERJUMP_ANGLE_DIFF;
    float x64_LUIGI_SUPERJUMP_VEL_X;
    float x68_LUIGI_SUPERJUMP_GRAVITY_START;
    float x6C_LUIGI_SUPERJUMP_VEL_Y;
    /// DOWN SPECIAL - LUIGI CYCLONE
    /// Vertical momentum from (first?) B button tap
    float x70_LUIGI_CYCLONE_TAP_MOMENTUM;
    float x74_LUIGI_CYCLONE_MOMENTUM_X_GROUND;
    float x78_LUIGI_CYCLONE_MOMENTUM_X_AIR;
    float x7C_LUIGI_CYCLONE_MOMENTUM_X_MUL_GROUND;
    float x80_LUIGI_CYCLONE_MOMENTUM_X_MUL_AIR;
    float x84_LUIGI_CYCLONE_FRICTION_END;
    s32 x88_LUIGI_CYCLONE_UNK;
    float x8C_LUIGI_CYCLONE_TAP_Y_VEL_MAX;
    float x90_LUIGI_CYCLONE_TAP_GRAVITY;
    s32 x94_LUIGI_CYCLONE_LANDING_LAG;
} LuigiAttr;

typedef struct MarioCharVar
{
    int var1;
    int var2;
    int var3;
    int var4;
    GOBJ *item_cape;
    int var6;
} MarioCharVar;

typedef struct FireballAttr
{
    float speed;
    float angle;
    float life;
    float unk1;
    float max_speed;
} FireballAttr;

typedef struct CapeItCmdFlags
{
	int spawn_effect1;
	int spawn_effect2;
} CapeItCmdFlags;

typedef struct SpecialNFtCmd
{
	int interruptable;
} SpecialNFtCmd;

typedef struct SpecialSFtCmd
{
	int create_wind;
	int enable_reflect;
	int spawn_cape;
} SpecialSFtCmd;

typedef struct SpecialSVar
{
	int reflect_enabled;
} SpecialSVar;


typedef struct SpecialHiFtCmd
{
	int can_control;
} SpecialHiFtCmd;


typedef struct SpecialLwFtCmd
{
	int decay_air_speed;
	int disable_rise; 		//?
    int can_control;
} SpecialLwFtCmd;

typedef struct SpecialLwVar
{
	float air_speed;	// x00
	int x04;			// x04
	int x08;			// x08
	float on_ground;	// x0C
} SpecialLwVar;


///////////////////////
//     Functions     //
///////////////////////

// 0xc4c508c
#define SPECIALS_TRANSITION_FLAGS (FIGHTER_GFX_PRESERVE | FIGHTER_HITSTATUS_COLANIM_PRESERVE | FIGHTER_MODEL_NOUPDATE | FIGHTER_ANIMVEL_NOUPDATE | FIGHTER_UNK_0x40 | FIGHTER_MATANIM_NOUPDATE | FIGHTER_THROW_EXCEPTION_NOUPDATE | FIGHTER_SFX_PRESERVE | FIGHTER_PARASOL_NOUPDATE)

// Think
void FireBallThink(GOBJ *);
void MarioCapeThink(GOBJ *);

// Special N
void SpecialN_AnimationCallback(GOBJ *gobj);
void SpecialN_IASACallback(GOBJ *gobj);
void SpecialN_PhysicCallback(GOBJ *gobj);
void SpecialN_CollisionCallback(GOBJ *gobj);

void spairn_anim(GOBJ *gobj);
void SpecialAirN_IASACallback(GOBJ *gobj);
void SpecialAirN_PhysicCallback(GOBJ *gobj);
void SpecialAirN_CollisionCallback(GOBJ *gobj);

// SpecialS
void SpecialS_AnimationCallback(GOBJ *gobj);
void SpecialS_IASACallback(GOBJ *gobj);
void SpecialS_PhysicCallback(GOBJ *gobj);
void SpecialS_CollisionCallback(GOBJ *gobj);

void SpecialAirS_AnimationCallback(GOBJ *gobj);
void SpecialAirS_IASACallback(GOBJ *gobj);
void SpecialAirS_PhysicCallback(GOBJ *gobj);
void SpecialAirS_CollisionCallback(GOBJ *gobj);
void SpecialAirSEnd_coll(GOBJ* gobj);
// Specialhi
void SpecialHi_AnimationCallback(GOBJ *gobj);
void SpecialHi_IASACallback(GOBJ *gobj);
void SpecialHi_PhysicCallback(GOBJ *gobj);
void SpecialHi_CollisionCallback(GOBJ *gobj);

void SpecialAirHi_AnimationCallback(GOBJ *gobj);
void SpecialAirHi_IASACallback(GOBJ *gobj);
void SpecialAirHi_PhysicCallback(GOBJ *gobj);
void SpecialAirHi_CollisionCallback(GOBJ *gobj);

// SpecialLw
void SpecialLw_AnimationCallback(GOBJ *gobj);
void SpecialLw_IASACallback(GOBJ *gobj);
void SpecialLw_PhysicCallback(GOBJ *gobj);
void SpecialLw_CollisionCallback(GOBJ *gobj);

void SpecialAirLw_AnimationCallback(GOBJ *gobj);
void SpecialAirLw_IASACallback(GOBJ *gobj);
void SpecialAirLw_PhysicCallback(GOBJ *gobj);

void SpecialAirLw_CollisionCallback(GOBJ *gobj);
void SpecialAirSStart_CollisionCallback(GOBJ* gobj);
void SpecialAirSHold_CollisionCallback(GOBJ* gobj);

void SpecialN_SpawnFireballThink(GOBJ *gobj);
void SpecialS_SpawnCapeThink(GOBJ *fighter);

// #define bool u8
// #define true 1
// #define false 0
#include <stdbool.h>

/// @brief checks item collision with any line and applies bounce physics if it touches any
/// @param item
/// @return TRUE if collision was made and FALSE otherwise
bool (*Item_Coll_Bounce)(GOBJ *item) = (int *)0x8027781c;

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
inline void *Item_GetItCmdFlags(GOBJ *item)
{
    return &((ItemData *)item->userdata)->itcmd_var;
}

/// @brief 
/// @param item 
/// @return 
inline void *Item_GetItemVar(GOBJ *item)
{
    return &((ItemData *)item->userdata)->item_var;
}

/// @brief Fighter Variables are used globally by the fighter
/// @param fighter GOBJ of Fighter
/// @return pointer to Fighter's "Fighter Variable" struct
inline void *Fighter_GetFighterVars(GOBJ *fighter)
{
	return &((FighterData *)fighter->userdata)->fighter_var;
}

inline void *Fighter_GetStateVars(GOBJ *fighter)
{
	return &((FighterData *)fighter->userdata)->state_var;
}

inline void *Fighter_GetScriptVars(GOBJ *fighter)
{
	return &((FighterData *)fighter->userdata)->ftcmd_var;
}

inline void *Fighter_GetSpecialAttributes(GOBJ *fighter)
{
	return ((FighterData *)fighter->userdata)->special_attributes;
}

#endif