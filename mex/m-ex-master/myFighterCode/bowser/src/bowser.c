#include "bowser.h"
//#include "special_lw.c"
#include "commonMoves.c"

/*
__attribute__((used)) static struct FtState move_logic[] = {
		// State: 341 - SpecialNStart
		{
			295,        // AnimationID
			0x340011,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x80134F48, // AnimationCallback
			0x801351B0, // IASACallback
			0x80135438, // PhysicsCallback
			0x801354F8, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 342 - SpecialN
		{
			296,        // AnimationID
			0x3C0011,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x80134F9C, // AnimationCallback
			0x801351B4, // IASACallback
			0x80135458, // PhysicsCallback
			0x80135564, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 343 - SpecialNEnd
		{
			297,        // AnimationID
			0x340011,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x80135040, // AnimationCallback
			0x801352F0, // IASACallback
			0x80135478, // PhysicsCallback
			0x801355D0, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 344 - SpecialAirNStart
		{
			298,        // AnimationID
			0x340411,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x8013507C, // AnimationCallback
			0x801352F4, // IASACallback
			0x80135498, // PhysicsCallback
			0x8013563C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 345 - SpecialAirN
		{
			299,        // AnimationID
			0x3C0411,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x801350D0, // AnimationCallback
			0x801352F8, // IASACallback
			0x801354B8, // PhysicsCallback
			0x801356A8, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 346 - SpecialAirNEnd
		{
			300,        // AnimationID
			0x340411,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x80135174, // AnimationCallback
			0x80135434, // IASACallback
			0x801354D8, // PhysicsCallback
			0x80135714, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 347 - SpecialSStart
		{
			301,        // AnimationID
			0x340012,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80133654, // AnimationCallback
			0x0,        // IASACallback
			0x80134224, // PhysicsCallback
			0x80134388, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 348 - SpecialSHit
		{
			302,        // AnimationID
			0x340012,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x801336CC, // AnimationCallback
			0x80133BF4, // IASACallback
			0x80134288, // PhysicsCallback
			0x801343D8, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 349 - SpecialSHit
		{
			303,        // AnimationID
			0x340012,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x801336CC, // AnimationCallback
			0x80133BF4, // IASACallback
			0x80134288, // PhysicsCallback
			0x801343D8, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 350 - SpecialSHit
		{
			302,        // AnimationID
			0x340012,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x801339AC, // AnimationCallback
			0x80133E4C, // IASACallback
			0x801342C8, // PhysicsCallback
			0x80134428, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 351 - SpecialSEndF
		{
			304,        // AnimationID
			0x340012,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x801339B4, // AnimationCallback
			0x0,        // IASACallback
			0x80134308, // PhysicsCallback
			0x80134478, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 352 - SpecialSEndB
		{
			305,        // AnimationID
			0x340012,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80133A90, // AnimationCallback
			0x0,        // IASACallback
			0x80134328, // PhysicsCallback
			0x801344A0, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 353 - SpecialAirSStart
		{
			306,        // AnimationID
			0x340412,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80133690, // AnimationCallback
			0x0,        // IASACallback
			0x80134244, // PhysicsCallback
			0x801343B0, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 354 - SpecialAirSHit
		{
			307,        // AnimationID
			0x340412,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x8013383C, // AnimationCallback
			0x80133D20, // IASACallback
			0x801342A8, // PhysicsCallback
			0x80134400, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 355 - SpecialAirSHit
		{
			308,        // AnimationID
			0x340412,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x8013383C, // AnimationCallback
			0x80133D20, // IASACallback
			0x801342A8, // PhysicsCallback
			0x80134400, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 356 - SpecialAirSHit
		{
			307,        // AnimationID
			0x340012,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x801339B0, // AnimationCallback
			0x80134038, // IASACallback
			0x801342E8, // PhysicsCallback
			0x80134450, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 357 - SpecialAirSEndF
		{
			309,        // AnimationID
			0x340412,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80133AD4, // AnimationCallback
			0x0,        // IASACallback
			0x80134348, // PhysicsCallback
			0x801344C8, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 358 - SpecialAirSEndB
		{
			310,        // AnimationID
			0x340412,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80133BB0, // AnimationCallback
			0x0,        // IASACallback
			0x80134368, // PhysicsCallback
			0x801344F0, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 359 - SpecialHi
		{
			311,        // AnimationID
			0x340213,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x80135C08, // AnimationCallback
			0x80135D78, // IASACallback
			0x80135D80, // PhysicsCallback
			0x80135E4C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 360 - SpecialAirHi
		{
			312,        // AnimationID
			0x340613,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x80135C60, // AnimationCallback
			0x80135D7C, // IASACallback
			0x80135DE0, // PhysicsCallback
			0x80135F6C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 361 - SpecialLw
		{
			313,        // AnimationID
			0x340214,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x8013474C, // AnimationCallback
			specialLw_IASACallback,        // IASACallback
			0x801347C4, // PhysicsCallback
			0x801348A0, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 362 - SpecialAirLw
		{
			314,        // AnimationID
			0x340614,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x80134788, // AnimationCallback
			specialAirLw_IASACallback,        // IASACallback
			0x80134804, // PhysicsCallback
			0x801348C0, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 363 - SpecialLwLanding
		{
			315,        // AnimationID
			0x340214,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			specialLwLanding_AnimCB, // AnimationCallback
			0x00000000,        // IASACallback
			0x80134A00, // PhysicsCallback
			0x80134A20, // CollisionCallback
			0x800761C8, // CameraCallback
		},
	};
*/
	