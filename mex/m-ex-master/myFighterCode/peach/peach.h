#ifndef PEACH_H
#define PEACH_H

#include "mex.h"

typedef struct PeachPrimaryAttributes {
	float weight;
	float gravity;
	float fallSpeed;

} PeachPrimaryAttributes;

#define PEACH_STOPFASTFALLING 100

#define GRAVITY_HITSTUN 1.6
#define FALL_SPEED_HITSTUN 2

#define GRAVITY_DECAY 0.01
#define FALL_SPEED_DECAY 0.002

#endif