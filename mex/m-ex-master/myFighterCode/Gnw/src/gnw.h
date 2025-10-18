#ifndef FT_GNW_H
#define FT_GNW_H

#include "mex.h"

#define SPECIALHI_CANCEL_MOMENTUM_DIVISOR 4

// commonMoveLogic.h
void SetCommonMoveLogic(FighterData* fp);
void OnLoad(GOBJ* fighter_gobj);
void OnDestroy(GOBJ* gobj);


void Gnw_SpecialHi_IASAcb(GOBJ* gobj);
void Gnw_SpecialAirHi_IASAcb(GOBJ* gobj);

void Gnw_SpecialHi_PhysCb(GOBJ* gobj);
void Gnw_SpecialAirHi_PhysCb(GOBJ* gobj);

void Gnw_SpecialAirLw_IASAcb(GOBJ* gobj);
void Gnw_SpecialLw_IASAcb(GOBJ* gobj);

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