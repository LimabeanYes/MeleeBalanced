#ifndef FT_NESS_H
#define FT_NESS_H

#include "mex.h"


///////////////////////
//      m-ex IDs     //
///////////////////////

///////////////////////
//    Vanilla IDs    //
///////////////////////

///////////////////////
//  Special States   //
///////////////////////

///////////////////////
//    Item States    //
///////////////////////


///////////////////////
//      Structs      //
///////////////////////

typedef struct NessCharVar
{

} NessCharVar;





///////////////////////
//     Functions     //
///////////////////////
void SpecialLwStart_IASACallback(GOBJ* gobj);
void SpecialAirLwStart_IASACallback(GOBJ* gobj);
void SpecialLwHold_IASACallback(GOBJ* gobj);
void SpecialAirLwHold_IASACallback(GOBJ* gobj);


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