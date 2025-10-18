#include "luigi.h"
#include "special_n.c"
#include "special_s.c"



__attribute__((used)) static struct FtState move_logic[] = {
		// State: 341 - SpecialN
		{
			295,        // AnimationID
			0x340111,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			0x8014275C, // AnimationCallback
			0x801427D4, // IASACallback
			0x80142834, // PhysicsCallback
			0x80142874, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 342 - SpecialAirN
		{
			296,        // AnimationID
			0x340511,   // StateFlags
			0x12,       // AttackID
			0x0,        // BitFlags
			spairn_anim, // AnimationCallback
			0x80142804, // IASACallback
			0x80142854, // PhysicsCallback
			SpecialAirN_CollisionCallback, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 343 - SpecialSStart
		{
			297,        // AnimationID
			0x340212,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80142C40, // AnimationCallback
			0x80142CB8, // IASACallback
			0x80142CC0, // PhysicsCallback
			0x80142D60, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 344 - SpecialSHold
		{
			298,        // AnimationID
			0x340212,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80142E98, // AnimationCallback
			0x80142FD8, // IASACallback
			0x80143038, // PhysicsCallback
			0x80143078, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 345 - SpecialS
		{
			301,        // AnimationID
			0x340212,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80143B18, // AnimationCallback
			0x80143B58, // IASACallback
			0x80143B60, // PhysicsCallback
			0x80143BE0, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 346 - SpecialSEnd
		{
			302,        // AnimationID
			0x340212,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80143D7C, // AnimationCallback
			0x80143DF4, // IASACallback
			0x80143DFC, // PhysicsCallback
			0x80143E8C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 347 - SpecialS
		{
			299,        // AnimationID
			0x340212,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80143258, // AnimationCallback
			0x801433A8, // IASACallback
			0x801433B0, // PhysicsCallback
			0x801433F0, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 348 - SpecialS
		{
			300,        // AnimationID
			0x340212,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x801436D8, // AnimationCallback
			0x80143828, // IASACallback
			0x80143830, // PhysicsCallback
			0x80143870, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 349 - SpecialAirSStart
		{
			303,        // AnimationID
			0x340612,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80142C7C, // AnimationCallback
			0x80142CBC, // IASACallback
			0x80142D00, // PhysicsCallback
			0x80142D9C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 350 - SpecialAirSHold
		{
			304,        // AnimationID
			0x340612,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80142F38, // AnimationCallback
			0x80143008, // IASACallback
			0x80143058, // PhysicsCallback
			0x801430B4, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 351 - SpecialS
		{
			301,        // AnimationID
			0x340612,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80143B1C, // AnimationCallback
			0x80143B5C, // IASACallback
			0x80143B64, // PhysicsCallback
			0x80143BE4, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 352 - SpecialAirSEnd
		{
			307,        // AnimationID
			0x340612,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80143DB8, // AnimationCallback
			0x80143DF8, // IASACallback
			0x80143E3C, // PhysicsCallback
			SpecialAirSEnd_coll, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 353 - SpecialS
		{
			305,        // AnimationID
			0x340612,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80143304, // AnimationCallback
			0x801433AC, // IASACallback
			0x801433D0, // PhysicsCallback
			0x8014342C, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 354 - SpecialS
		{
			306,        // AnimationID
			0x340612,   // StateFlags
			0x13,       // AttackID
			0x0,        // BitFlags
			0x80143784, // AnimationCallback
			0x8014382C, // IASACallback
			0x80143850, // PhysicsCallback
			0x801438AC, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 355 - SpecialHi
		{
			308,        // AnimationID
			0x340213,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x80144098, // AnimationCallback
			0x80144158, // IASACallback
			0x801443E8, // PhysicsCallback
			0x801444E4, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 356 - SpecialAirHi
		{
			309,        // AnimationID
			0x340613,   // StateFlags
			0x14,       // AttackID
			0x0,        // BitFlags
			0x801440F8, // AnimationCallback
			0x801442A0, // IASACallback
			0x80144420, // PhysicsCallback
			0x80144554, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 357 - SpecialLw
		{
			310,        // AnimationID
			0x340214,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x80144830, // AnimationCallback
			0x80144950, // IASACallback
			0x80144958, // PhysicsCallback
			0x80144B38, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 358 - SpecialAirLw
		{
			311,        // AnimationID
			0x340614,   // StateFlags
			0x15,       // AttackID
			0x0,        // BitFlags
			0x8014487C, // AnimationCallback
			0x80144954, // IASACallback
			0x80144A7C, // PhysicsCallback
			0x80144CEC, // CollisionCallback
			0x800761C8, // CameraCallback
		},
		// State: 359 - RunBrake
		{
			14,         // AnimationID
			0x0,        // StateFlags
			0x1,        // AttackID
			0x0,        // BitFlags
			0x0,        // AnimationCallback
			0x0,        // IASACallback
			0x800C7158, // PhysicsCallback
			0x0,        // CollisionCallback
			0x0,        // CameraCallback
		},
		// State: 360 - Landing
		{
			15,         // AnimationID
			0x0,        // StateFlags
			0x1,        // AttackID
			0x0,        // BitFlags
			0x0,        // AnimationCallback
			0x0,        // IASACallback
			0x800C7200, // PhysicsCallback
			0x0,        // CollisionCallback
			0x0,        // CameraCallback
		},
	};