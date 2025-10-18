#include "cap.h"

void SpecialS_OnLand(GOBJ* gobj){
    FighterData* fighter_data = gobj->userdata;
    Fighter_EnterSpecialLanding(gobj, 0, 18);
    return;
}

void ftCa_SpecialAirS_Coll(GOBJ* gobj){
    FighterData* fighter_data = gobj->userdata;
    Fighter_CollAir_GrabBothLedgesWalljump(gobj, SpecialS_OnLand);
}

void ftCa_SpecialAirSStart_Coll(GOBJ* gobj)
{
    FighterData* fighter_data = gobj->userdata;
    CapCharVar* charvar = &fighter_data->fighter_var;
    if (charvar->hasbeenused_specials == 0 && Fighter_IASACheck_WallJump(gobj) == 1) {
        charvar->hasbeenused_specials = 1;
        Fighter_CollAir_GrabBothLedgesWalljump(gobj, SpecialS_OnLand);
    }
    if (Fighter_CheckNearbyLedges(gobj) != 0 && Fighter_CheckForOtherFighterOnLedge(gobj) == 0) {
        Fighter_EnterCliffCatch(gobj);
    }
    if (Fighter_CollAir_IgnoreLedge_NoCB(gobj) != 0) {
        fighter_data->phys.self_vel_ground.X = fighter_data->phys.self_vel.X;
        Effect_DestroyAll(gobj);
        Fighter_EnterSpecialLanding(gobj, 0, 18);
    }
}

void ftCa_SpecialS_Coll(GOBJ* gobj){
    FighterData* fighter_data = gobj->userdata;
    Fighter_CollAir_GrabBothLedgesWalljump(gobj, SpecialS_OnLand);
    if (Fighter_CollGround_PassLedge(gobj)==0) {
        Effect_DestroyAll(gobj);
        Fighter_EnterFall(gobj);
        return;
    }
}

void ftCa_SpecialSStart_Coll(GOBJ* gobj)
{
    FighterData* fighter_data = gobj->userdata;
    if (fighter_data->phys.air_state == 1){
        Fighter_CollAir_GrabBothLedgesWalljump(gobj, SpecialS_OnLand);
    }
    else {
        if (fighter_data->ftcmd_var.flag2 == 0) {
            Fighter_CollGround_StopLedge_EnterFall(gobj);
            return;
        }
        if (Fighter_CollGround_PassLedge(gobj) == 0) {
            Effect_DestroyAll(gobj);
            Fighter_EnterFall(gobj);
            return;
        }
        if (fighter_data->ftcmd_var.flag0 == 1) {
            float _ = fighter_data->facing_direction;
            if ((fighter_data->facing_direction == +1 && (fighter_data->coll_data.envFlags & ECB_WALLRIGHT)) ||
                (fighter_data->facing_direction == -1 && fighter_data->coll_data.envFlags & ECB_WALLLEFT)){
                Effect_DestroyAll(gobj);
                Fighter_EnterWait(gobj);
            }
        }
    }
}