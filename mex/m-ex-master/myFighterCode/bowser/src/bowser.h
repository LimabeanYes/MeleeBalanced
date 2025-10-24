#ifndef FT_KOOPA_H
#define FT_KOOPA_H

#include "mex.h"

#define ARMOUR_CONST 75

#define ARMOUR_VALUES {75, 100, 75, 120}

enum armourKind {
    DEFAULT,
    FSMASH_ARMOUR,
    UPSMASH_ARMOUR,
    UPAIR_ARMOUR,
    NUMBER_OF_ARMOURS
};

int armour_values[NUMBER_OF_ARMOURS] = ARMOUR_VALUES;

#define STATE_SPECIALN 347
#define STATE_SPECIALNAIR 348
#define STATE_SPECIALS 350
#define STATE_SPECIALSAIR 352
#define STATE_SPECIALHI 359
#define STATE_SPECIALHIAIR 354
#define STATE_SPECIALLW 361
#define STATE_SPECIALLWAIR 362
#define STATE_SPECIALLWLAND 363

///////////////////////
//    Item States    //
///////////////////////

#define STATE_FIREBALL 0

///////////////////////
//      Structs      //
///////////////////////

typedef struct koopaAttr {
    float x0;
    u32 x4;
    float x8;
    float xC;
    float x10;
    float x14;
    float x18;
    float x1C;
    u32 x20;
    float x24;
    float x28;
    u32 x2C;
    float x30;
    float x34;
    float x38;
    float x3C;
    float x40;
    float x44;
    float x48;
    float x4C;
    u32 unk50;
    float x54;
    float x58;
    float x5C;
    float x60;
    float x64;
    float x68;
    float x6C;
    float x70;
    float x74;
    float x78;
    float x7C;
    float x80;
    float x84;
    float x88;
    float x8C;
    float x90;
    float x94;
    float x98;
    float x9C;
} koopaAttr;

typedef struct koopCharVar
{
    /* 0x222C */ float x222C;
    /* 0x2230 */ float x2230;
} koopsCharVar;

typedef struct lw3Flags {
    int A_hasBeenPressed;
};





typedef struct SpecialSFtCmd
{
	int create_wind;
	int enable_reflect;
	int spawn_cape;
} SpecialSFtCmd;

typedef struct SpecialLwVar
{
    int lockout;
    
} SpecialLwVar;

typedef struct Lw3Var
{
    int a_hasBeenPressed;

} Lw3Var;



///////////////////////
//     Functions     //
///////////////////////

// 0xc4c508c
#define SPECIALS_TRANSITION_FLAGS (FIGHTER_GFX_PRESERVE | FIGHTER_HITSTATUS_COLANIM_PRESERVE | FIGHTER_MODEL_NOUPDATE | FIGHTER_ANIMVEL_NOUPDATE | FIGHTER_UNK_0x40 | FIGHTER_MATANIM_NOUPDATE | FIGHTER_THROW_EXCEPTION_NOUPDATE | FIGHTER_SFX_PRESERVE | FIGHTER_PARASOL_NOUPDATE)

// SpecialS
void ftCa_SpecialAirS_Coll(GOBJ* gobj);
void ftCa_SpecialAirSStart_Coll(GOBJ* gobj);
void ftCa_SpecialS_Coll(GOBJ* gobj);
void ftCa_SpecialSStart_Coll(GOBJ* gobj);

void specialLw_IASACallback(GOBJ* gobj);
void specialAirLw_IASACallback(GOBJ* gobj);
void specialLwLanding_IASACallback(GOBJ* gobj);

void specialLwLanding_AnimCB(GOBJ* gobj);



// #define bool u8
// #define true 1
// #define false 0
#include <stdbool.h>

/// @brief checks item collision with any line and applies bounce physics if it touches any
/// @param item
/// @return TRUE if collision was made and FALSE otherwise


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


/// @brief 
/// @param item 
/// @return 


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