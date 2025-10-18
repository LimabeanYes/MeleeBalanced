#include "luigi.h"

void resetGrav(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	fd->attr.gravity = fd->attr.gravity / gravChanger;
}

void SpecialAirN(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	void (*cb)(GOBJ * gobj) = (void*)0x801426EC;
	cb(gobj);
	fd->attr.gravity = fd->attr.gravity * gravChanger;
	fd->cb.EnterHitlag = resetGrav;
	fd->cb.OnTakeDamage = resetGrav;
	return;
}
void SpecialN_OnLand(GOBJ* gobj)
{
	FighterData* fd = gobj->userdata;
	int landLag = FIREBALL_LANDING_LAG;
	if (HSD_Randi(4) == 1) {
		landLag -= 2;
		if (HSD_Randi(4) == 1) {
			landLag -= 2;
		}
	}
	resetGrav(gobj);
	Fighter_EnterSpecialLanding(gobj, 0, landLag);
	return;
}
void SpecialAirN_CollisionCallback(GOBJ* gobj)
{
	Fighter_CollAir_IgnoreLedge(gobj, SpecialN_OnLand);
	void (*cb)(GOBJ * gobj) = (void*)0x801428E8;
	cb(gobj);
	return;
}

void spairn_anim(GOBJ* gobj)
{
	FighterData* fd = gobj->userdata;
	if (FrameTimerCheck(gobj) == 0) {
		resetGrav(gobj);
		Fighter_EnterFall(gobj);
	}
	return;
}