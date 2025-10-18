#include "cap.h"
#include "special_s.c"
#include "special_n.c"
#include "special_lw.c"
#include "special_hi.c"

//For side special, I've made it so that you can cancel with a wall jump, however, that means we need to limit number of uses of side b, until he lands again.
void onlanding(GOBJ* gobj) {
	FighterData* fd = gobj->userdata;
	CapCharVar* charvar = &fd->fighter_var;
	charvar->hasbeenused_specials = 0;
}

/*this table is used to define move logic for fighter states
* each state needs to have a callback for physics, animation, collision and interrupts. Camera callback should not change
* for states that are default, ie the ones used in the base game, they should just use the memory addresses already in the table
* for our own custom states, we can just write them and replace the callback for the move we're changing.
*/


__attribute__((used)) static struct FtState move_logic[] = {
		// State: 341 - Swing42
		{
			295,        // AnimationID
			0x440842,   // StateFlags
			0x41,       // AttackID
			0x0,        // BitFlags
			0x800CD390, // AnimationCallback
			0x800CD3B0, // IASACallback
			0x800CD3D0, // PhysicsCallback
			0x800CD3F0, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 342 - Swing42
		{
			296,        // AnimationID
			0x440846,   // StateFlags
			0x45,       // AttackID
			0x0,        // BitFlags
			0x800CD458, // AnimationCallback
			0x800CD478, // IASACallback
			0x800CD498, // PhysicsCallback
			0x800CD4B8, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 343 - Swing42
		{
			297,        // AnimationID
			0x44084A,   // StateFlags
			0x49,       // AttackID
			0x0,        // BitFlags
			0x800CD520, // AnimationCallback
			0x800CD540, // IASACallback
			0x800CD560, // PhysicsCallback
			0x800CD580, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 344 - Swing42
		{
			298,        // AnimationID
			0x44084E,   // StateFlags
			0x4D,       // AttackID
			0x0,        // BitFlags
			0x800CD6A0, // AnimationCallback
			0x800CD7C4, // IASACallback
			0x800CD7E4, // PhysicsCallback
			0x800CD804, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 345 - Swing42
		{
			299,        // AnimationID
			0x440852,   // StateFlags
			0x51,       // AttackID
			0x0,        // BitFlags
			0x800CD88C, // AnimationCallback
			0x800CD8AC, // IASACallback
			0x800CD8CC, // PhysicsCallback
			0x800CD8EC, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 346 - Swing42
		{
			300,        // AnimationID
			0x440856,   // StateFlags
			0x55,       // AttackID
			0x0,        // BitFlags
			0x800CDB14, // AnimationCallback
			0x800CDB34, // IASACallback
			0x800CDB54, // PhysicsCallback
			0x800CDB74, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 347 - SpecialN
		{
			301,        // AnimationID
			0x340211,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			specialN_AnimCallback, // AnimationCallback
			0x800E2E38, // IASACallback
			specialN_PhysCallback, // PhysicsCallback
			0x800E3168, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 348 - SpecialAirN
		{
			302,        // AnimationID
			0x340611,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			specialAirN_AnimCallback, // AnimationCallback
			0x800E2E3C, // IASACallback
			specialAirN_PhysCallback, // PhysicsCallback
			0x800E31F4, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 349 - SpecialSStart
		{
			303,        // AnimationID
			0x340212,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x800E384C, // AnimationCallback
			0x800E3B0C, // IASACallback
			0x800E3B1C, // PhysicsCallback
			ftCa_SpecialSStart_Coll, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 350 - SpecialS
		{
			304,        // AnimationID
			0x340212,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x800E3888, // AnimationCallback
			0x800E3B10, // IASACallback
			0x800E3B3C, // PhysicsCallback
			ftCa_SpecialS_Coll, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 351 - SpecialAirSStart
		{
			305,        // AnimationID
			0x340612,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x800E3964, // AnimationCallback
			0x800E3B14, // IASACallback
			0x800E3B5C, // PhysicsCallback
			ftCa_SpecialAirSStart_Coll, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 352 - SpecialAirS
		{
			306,        // AnimationID
			0x340612,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x800E39F0, // AnimationCallback
			0x800E3B18, // IASACallback
			0x800E3BD0, // PhysicsCallback
			ftCa_SpecialAirS_Coll, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 353 - SpecialHi
		{
			307,        // AnimationID
			0x340013,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x800E4B00, // AnimationCallback
			0x800E4B60, // IASACallback
			0x800E4BF8, // PhysicsCallback
			0x800E4E1C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 354 - SpecialAirHi
		{
			308,        // AnimationID
			0x340413,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x800E4EE8, // AnimationCallback
			0x800E4F48, // IASACallback
			0x800E4FDC, // PhysicsCallback
			0x800E50D8, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 355 - SpecialHiCatch
		{
			309,        // AnimationID
			0x340013,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x800E51F8, // AnimationCallback
			0x800E5234, // IASACallback
			0x800E5238, // PhysicsCallback
			0x800E523C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 356 - SpecialHiThrow
		{
			310,        // AnimationID
			0x340013,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			specialHi_hitAnimCb, // AnimationCallback
			0x800E5384, // IASACallback
			0x800E5388, // PhysicsCallback
			specialHi_hit1Coll, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 357 - SpecialLw
		{
			311,        // AnimationID
			0x340214,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x800E415C, // AnimationCallback
			specialLw_IasaCb,        // IASACallback
			0x800E4408, // PhysicsCallback
			0x800E46B8, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 358 - SpecialLwEnd
		{
			312,        // AnimationID
			0x340214,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x800E4268, // AnimationCallback
			0x0,        // IASACallback
			0x800E449C, // PhysicsCallback
			0x800E47B0, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 359 - SpecialAirLw
		{
			313,        // AnimationID
			0x340614,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x800E42E0, // AnimationCallback
			0x0,        // IASACallback
			0x800E45E4, // PhysicsCallback
			0x800E48BC, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 360 - SpecialAirLwEnd
		{
			314,        // AnimationID
			0x340614,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x800E4354, // AnimationCallback
			0x0,        // IASACallback
			0x800E4618, // PhysicsCallback
			0x800E493C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 361 - SpecialAirLwEndAir
		{
			316,        // AnimationID
			0x340614,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x800E4390, // AnimationCallback
			0x0,        // IASACallback
			0x800E4678, // PhysicsCallback
			0x800E495C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 362 - SpecialLwEndAir
		{
			315,        // AnimationID
			0x340214,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x800E42A4, // AnimationCallback
			0x0,        // IASACallback
			0x800E455C, // PhysicsCallback
			0x800E4838, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 363 - SpecialHiThrow
		{
			317,        // AnimationID
			0x340614,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			specialHi_hitAnimCb, // AnimationCallback
			0x0,        // IASACallback
			0x800E4698, // PhysicsCallback
			specialHi_hit1Coll, // CollisionCallback
			0x800761C8, // CameraCallback
		},
	};


