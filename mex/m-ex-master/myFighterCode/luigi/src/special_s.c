#include "mex.h"

void SpecialS_OnLand(GOBJ* gobj)
{
	int landLag = S_LAND_LAG;
	if (HSD_Randi(4) == 1) {
		landLag -= 4;
		if (HSD_Randi(4) == 1) {
			landLag -= 4;
		}
	}
	Fighter_EnterSpecialLanding(gobj, 0, landLag);
	return;
}

void SpecialAirSStart_CollisionCallback(GOBJ* gobj)
{
	Fighter_CollAir_GrabFacingLedgeWalljump(gobj, Fighter_Coll_CheckToPass, SpecialS_OnLand);
	void (*cb)(GOBJ * gobj) = (void*)0x801428E8;
	cb(gobj);
	return;
}
void SpecialAirSHold_CollisionCallback(GOBJ* gobj) {
	Fighter_CollAir_GrabFacingLedgeWalljump(gobj, Fighter_Coll_CheckToPass, SpecialS_OnLand);
	void (*cb)(GOBJ * gobj) = (void*)0x801428E8;
	cb(gobj);
	return;
}


void SpecialAirSEnd_coll(GOBJ* gobj) {
	Fighter_CollAir_GrabFacingLedgeWalljump(gobj, Fighter_Coll_CheckToPass, SpecialS_OnLand);
	void (*cb)(GOBJ * gobj) = (void*)0x801428E8;
	cb(gobj);
	return;
}