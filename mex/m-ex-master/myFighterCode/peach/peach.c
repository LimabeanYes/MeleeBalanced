#include "peach.h"

//store peach's base attributes for fall speed stuff
static PeachPrimaryAttributes peachAttrs;

void onFrame(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	int countAsHitstun = fd->fighter_var.ft_var52;
	if (fd->flags.hitstun != 0) countAsHitstun = 1;
	if (fd->state_id == ASID_WAIT || fd->state_id == ASID_FALL) {
		countAsHitstun = 0;
		fd->attr.gravity = peachAttrs.gravity;
		fd->attr.terminal_velocity = peachAttrs.fallSpeed;
	}
	if (countAsHitstun != 0 && fd->dmg.percent <= PEACH_STOPFASTFALLING) {
		fd->attr.gravity = GRAVITY_HITSTUN;
		fd->attr.terminal_velocity = FALL_SPEED_HITSTUN;
	}
	else {
		if (fd->attr.gravity != peachAttrs.gravity) {
			fd->attr.gravity -= GRAVITY_DECAY;
			if (fd->attr.gravity < peachAttrs.gravity) {
				fd->attr.gravity = peachAttrs.gravity;
			}
		}
		if(fd->attr.terminal_velocity != peachAttrs.fallSpeed) {
			fd->attr.terminal_velocity -= FALL_SPEED_DECAY;
			if (fd->attr.terminal_velocity < peachAttrs.fallSpeed) {
				fd->attr.terminal_velocity = peachAttrs.fallSpeed;
			}
		}
	}
	//OSReport("gravity: %f, fallSpeed: %f\n\n", fd->attr.gravity, fd->attr.terminal_velocity);
}

void onLoad(GOBJ* gobj) {
	void* (*cb)(GOBJ * gobj) = (int*)0x8011B628;
	cb(gobj);

	FighterData* fd = gobj->userdata;

	peachAttrs.gravity = fd->attr.gravity;
	peachAttrs.fallSpeed = fd->attr.terminal_velocity;
	fd->fighter_var.ft_var52 = 0;
}