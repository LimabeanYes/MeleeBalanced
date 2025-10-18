#ifndef FT_CAP_H
#define FT_CAP_H

#include "mex.h"

typedef struct CapCharVar
{
    /* 0x222C */ int during_specials_start;
    /* 0x2230 */ int during_specials;
    /* 0x2234 */ int hasbeenused_specials;
} CapCharVar;



void specialHi_hitAnimCb(GOBJ* gobj);
void specialHi_hit1Coll(GOBJ* gobj);
void specialHi_hit2Coll(GOBJ* gobj);
typedef struct SpecialSFtCmd
{
	int create_wind;
	int enable_reflect;
	int spawn_cape;
} SpecialSFtCmd;

typedef struct SpecialSVar
{
    float grav;
} SpecialSVar;

typedef struct SpecialNVar
{
    float speed;
} SpecialNVar;
typedef struct SpecialNFlag
{
    int change;
} SpecialNFlag;


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

void specialAirN_PhysCallback(GOBJ* gobj);
void specialN_PhysCallback(GOBJ* gobj);

void specialAirN_AnimCallback(GOBJ* gobj);
void specialN_AnimCallback(GOBJ* gobj);


// #define bool u8
// #define true 1
// #define false 0
#include <stdbool.h>

/// @brief checks item collision with any line and applies bounce physics if it touches any
/// @param item
/// @return TRUE if collision was made and FALSE otherwise

void specialLw_IasaCb(GOBJ* gobj);
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