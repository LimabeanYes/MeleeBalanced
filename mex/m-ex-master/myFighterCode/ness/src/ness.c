#include "ness.h"
#include "special_lw.c"

__attribute__((used)) static struct FtState move_logic[] = {
		// State: 341 - AttackS4
		{
			62,         // AnimationID
			0x241A09,   // StateFlags
			0xA,        // AttackID
			0x0,        // BitFlags
			0x80114D50, // AnimationCallback
			0x80114E04, // IASACallback
			0x80114E64, // PhysicsCallback
			0x80114E98, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 342 - AttackHi4
		{
			66,         // AnimationID
			0x240A0A,   // StateFlags
			0xB,        // AttackID
			0x80,       // BitFlags
			0x80115C9C, // AnimationCallback
			0x80115E74, // IASACallback
			0x80115EB8, // PhysicsCallback
			0x80115F14, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 343 - AttackHi4
		{
			295,        // AnimationID
			0x24080A,   // StateFlags
			0xB,        // AttackID
			0x0,        // BitFlags
			0x80115F88, // AnimationCallback
			0x801160B4, // IASACallback
			0x801160E4, // PhysicsCallback
			0x80116104, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 344 - AttackHi4
		{
			296,        // AnimationID
			0x24080A,   // StateFlags
			0xB,        // AttackID
			0x0,        // BitFlags
			0x8011620C, // AnimationCallback
			0x801162B0, // IASACallback
			0x801162E0, // PhysicsCallback
			0x80116420, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 345 - AttackLw4
		{
			67,         // AnimationID
			0x240A0B,   // StateFlags
			0xC,        // AttackID
			0x80,       // BitFlags
			0x80116638, // AnimationCallback
			0x801166D4, // IASACallback
			0x80116718, // PhysicsCallback
			0x8011674C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 346 - AttackLw4
		{
			297,        // AnimationID
			0x24080B,   // StateFlags
			0xC,        // AttackID
			0x0,        // BitFlags
			0x80116798, // AnimationCallback
			0x80116828, // IASACallback
			0x80116858, // PhysicsCallback
			0x80116878, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 347 - AttackLw4
		{
			298,        // AnimationID
			0x24080B,   // StateFlags
			0xC,        // AttackID
			0x0,        // BitFlags
			0x80116958, // AnimationCallback
			0x801169BC, // IASACallback
			0x801169EC, // PhysicsCallback
			0x80116A9C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 348 - SpecialNStart
		{
			299,        // AnimationID
			0x340111,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x801170DC, // AnimationCallback
			0x80117648, // IASACallback
			0x80117750, // PhysicsCallback
			0x801178E8, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 349 - SpecialNHold
		{
			300,        // AnimationID
			0x340111,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x801171BC, // AnimationCallback
			0x8011764C, // IASACallback
			0x80117788, // PhysicsCallback
			0x80117954, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 350 - SpecialNHold
		{
			301,        // AnimationID
			0x340111,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x801171BC, // AnimationCallback
			0x8011764C, // IASACallback
			0x80117788, // PhysicsCallback
			0x80117954, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 351 - SpecialNEnd
		{
			302,        // AnimationID
			0x340111,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x801172F0, // AnimationCallback
			0x801176C8, // IASACallback
			0x801177A8, // PhysicsCallback
			0x801179C0, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 352 - SpecialAirNStart
		{
			303,        // AnimationID
			0x340511,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x80117378, // AnimationCallback
			0x801176CC, // IASACallback
			0x801177C8, // PhysicsCallback
			0x80117A2C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 353 - SpecialAirNHold
		{
			304,        // AnimationID
			0x340511,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x80117458, // AnimationCallback
			0x801176D0, // IASACallback
			0x80117828, // PhysicsCallback
			0x80117A98, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 354 - SpecialAirNHold
		{
			305,        // AnimationID
			0x340511,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x80117458, // AnimationCallback
			0x801176D0, // IASACallback
			0x80117828, // PhysicsCallback
			0x80117A98, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 355 - SpecialAirNEnd
		{
			306,        // AnimationID
			0x340511,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x8011758C, // AnimationCallback
			0x8011774C, // IASACallback
			0x80117888, // PhysicsCallback
			0x80117B04, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 356 - SpecialS
		{
			307,        // AnimationID
			0x340112,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80116D74, // AnimationCallback
			0x0,        // IASACallback
			0x80116DEC, // PhysicsCallback
			0x80116E2C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 357 - SpecialAirS
		{
			308,        // AnimationID
			0x340512,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80116DB0, // AnimationCallback
			0x0,        // IASACallback
			0x80116E0C, // PhysicsCallback
			0x80116E68, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 358 - SpecialHiStart
		{
			309,        // AnimationID
			0x340113,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x801186B0, // AnimationCallback
			0x80118F80, // IASACallback
			0x80118FA4, // PhysicsCallback
			0x80119460, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 359 - SpecialHiHold
		{
			310,        // AnimationID
			0x340113,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x801187A4, // AnimationCallback
			0x80118F84, // IASACallback
			0x80118FDC, // PhysicsCallback
			0x801194CC, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 360 - SpecialHiEnd
		{
			311,        // AnimationID
			0x340113,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x80118900, // AnimationCallback
			0x80118F88, // IASACallback
			0x80118FFC, // PhysicsCallback
			0x80119538, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 361 - SpecialHi
		{
			312,        // AnimationID
			0x340113,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x8011893C, // AnimationCallback
			0x80118F8C, // IASACallback
			0x8011901C, // PhysicsCallback
			0x801195A4, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 362 - SpecialAirHiStart
		{
			313,        // AnimationID
			0x340513,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x80118A10, // AnimationCallback
			0x80118F90, // IASACallback
			0x80119134, // PhysicsCallback
			0x80119798, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 363 - SpecialAirHiHold
		{
			314,        // AnimationID
			0x340513,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x80118B04, // AnimationCallback
			0x80118F94, // IASACallback
			0x80119194, // PhysicsCallback
			0x80119804, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 364 - SpecialAirHiEnd
		{
			315,        // AnimationID
			0x340513,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x80118D60, // AnimationCallback
			0x80118F98, // IASACallback
			0x801191F4, // PhysicsCallback
			0x80119870, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 365 - SpecialHi
		{
			316,        // AnimationID
			0x340513,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x80118DF8, // AnimationCallback
			0x80118F9C, // IASACallback
			0x80119254, // PhysicsCallback
			0x801198DC, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 366 - DamageFall
		{
			317,        // AnimationID
			0x340113,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x80118EF0, // AnimationCallback
			0x80118FA0, // IASACallback
			0x80119410, // PhysicsCallback
			0x80119D58, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 367 - SpecialLwStart
		{
			318,        // AnimationID
			0x340014,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x80119F20, // AnimationCallback
			SpecialLwStart_IASACallback, // IASACallback
			0x8011A0E8, // PhysicsCallback
			0x8011A168, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 368 - SpecialLwHold
		{
			319,        // AnimationID
			0x3C0014,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x8011A2A8, // AnimationCallback
			SpecialLwHold_IASACallback, // IASACallback
			0x8011A440, // PhysicsCallback
			0x8011A4E8, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 369 - SpecialLwHit
		{
			320,        // AnimationID
			0x340014,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x8011ABF8, // AnimationCallback
			0x8011AEE0, // IASACallback
			0x8011AEE8, // PhysicsCallback
			0x8011AF90, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 370 - SpecialLwEnd
		{
			321,        // AnimationID
			0x340014,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x8011B25C, // AnimationCallback
			0x8011B2E4, // IASACallback
			0x8011B2EC, // PhysicsCallback
			0x8011B36C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 371 - SpecialLwHold
		{
			319,        // AnimationID
			0x340014,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x8011A700, // AnimationCallback
			0x8011A920, // IASACallback
			0x8011A928, // PhysicsCallback
			0x8011A9D0, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 372 - SpecialAirLwStart
		{
			322,        // AnimationID
			0x340414,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x8011A000, // AnimationCallback
			SpecialAirLwStart_IASACallback, // IASACallback
			0x8011A108, // PhysicsCallback
			0x8011A1A4, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 373 - SpecialAirLwHold
		{
			323,        // AnimationID
			0x3C0414,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x8011A370, // AnimationCallback
			SpecialAirLwHold_IASACallback, // IASACallback
			0x8011A474, // PhysicsCallback
			0x8011A524, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 374 - SpecialAirLwHit
		{
			324,        // AnimationID
			0x340414,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x8011ADC8, // AnimationCallback
			0x8011AEE4, // IASACallback
			0x8011AF1C, // PhysicsCallback
			0x8011AFCC, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 375 - SpecialAirLwEnd
		{
			325,        // AnimationID
			0x340414,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x8011B2A0, // AnimationCallback
			0x8011B2E8, // IASACallback
			0x8011B30C, // PhysicsCallback
			0x8011B3A8, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 376 - SpecialAirLwHold
		{
			323,        // AnimationID
			0x340414,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x8011A810, // AnimationCallback
			0x8011A924, // IASACallback
			0x8011A95C, // PhysicsCallback
			0x8011AA0C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
	};