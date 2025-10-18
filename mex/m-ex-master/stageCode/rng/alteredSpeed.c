#include "rng.h"

typedef struct attrReset                                                // 0x110
{                                                          //
    float walk_initial_velocity;                           // 0x110
    float walk_acceleration;                               // 0x114
    float walk_maximum_velocity;                           // 0x118
    float slow_walk_max;                                   // 0x11C
    float mid_walk_point;                                  // 0x120
    float fast_walk_min;                                   // 0x124
    float ground_friction;                                 // 0x128
    float dash_initial_velocity;                           // 0x12C
    float dashrun_acceleration_a;                          // 0x130
    float dashrun_acceleration_b;                          // 0x134
    float dashrun_terminal_velocity;                       // 0x138
    float run_animation_scaling;                           // 0x13C
    float max_runbrake_frames;                             // 0x140
    float grounded_max_horizontal_velocity;                // 0x144
    float jump_startup_time;                               // 0x148
    float jump_h_initial_velocity;                         // 0x14C
    float jump_v_initial_velocity;                         // 0x150
    float ground_to_air_jump_momentum_multiplier;          // 0x154
    float jump_h_max_velocity;                             // 0x158
    float hop_v_initial_velocity;                          // 0x15C
    float air_jump_v_multiplier;                           // 0x160
    float air_jump_h_multiplier;                           // 0x164
    int max_jumps;                                         // 0x168
    float gravity;                                         // 0x16C
    float terminal_velocity;                               // 0x170
    float aerial_drift_stick_mult;                         // 0x174
    float aerial_drift_base;                               // 0x178, minimum amount of drift, stick mult is added on top of this
    float aerial_drift_max;                                // 0x17C
    float aerial_friction;                                 // 0x180
    float fastfall_velocity;                               // 0x184
    float horizontal_air_mobility_constant;                // 0x188
    int jab_2_input_window;                                // 0x18C
    int jab_3_input_window;                                // 0x190
    int frames_to_change_direction_on_standing_turn;       // 0x194
    float weight;                                          // 0x198
    float model_scaling;                                   // 0x19C
    float initial_shield_size;                             // 0x1A0
    float shield_break_initial_velocity;                   // 0x1A4
    int rapid_jab_window;                                  // 0x1A8
    float rebound_frames;                                  // 0x1AC
    int x1B0;                                              // 0x1B0
    int x1B4;                                              // 0x1B4
    float ledge_jump_horizontal_velocity;                  // 0x1B8
    float ledge_jump_vertical_velocity;                    // 0x1BC
    float item_throw_velocity_multiplier;                  // 0x1C0
    float item_discard_vel_mult;                           // 0x1C4
    int x1C8;                                              // 0x1C8
    int x1CC;                                              // 0x1CC
    int x1D0;                                              // 0x1D0
    int x1D4;                                              // 0x1D4
    int x1D8;                                              // 0x1D8
    int x1DC;                                              // 0x1DC
    int x1E0;                                              // 0x1E0
    int x1E4;                                              // 0x1E4
    int x1E8;                                              // 0x1E8
    float kirby_star_scaling;                              // 0x1EC
    float kirby_b_star_damage;                             // 0x1F0
    float normal_landing_lag;                              // 0x1F4
    float n_air_landing_lag;                               // 0x1F8
    float f_air_landing_lag;                               // 0x1FC
    float b_air_landing_lag;                               // 0x200
    float u_air_landing_lag;                               // 0x204
    float d_air_landing_lag;                               // 0x208
    float nametag_height;                                  // 0x20C
    float wall_tech_x_offset;                              // 0x210
    float wall_jump_horizontal_velocity;                   // 0x214
    float wall_jump_vertical_velocity;                     // 0x218
    int x21C;                                              // 0x21C
    float trophy_scale;                                    // 0x220
    Vec3 bunny_hood_left_offset;                           // 0x224
    Vec3 bunny_hood_right_offset;                          // 0x230
    float bunny_hood_scale;                                // 0x23C
    Vec3 head_flower_offset;                               // 0x240
    float head_flower_scale;                               // 0x24C
    int x250;                                              // 0x250
    int x254;                                              // 0x254
    int unk_walljump;                                      // 0x258,
    float bubble_ratio;                                    // 0x25C
    int x260;                                              // 0x260
    int x264;                                              // 0x264
    int x268;                                              // 0x268
    int x26C;                                              // 0x26C
    float respawn_platform_scale;                          // 0x270
    int x274;                                              // 0x274
    int x278;                                              // 0x278
    int camera_zoom_target_bone;                           // 0x27C
    int x280;                                              // 0x280
    int x284;                                              // 0x284
    int x288;                                              // 0x288
    int special_jump_action___1;                           // 0x28C
    int weight_dependent_throw_speed_flags;                // 0x290
} attrReset;

static attrReset ogAttributes[4];

void randEvent_speedAlter_apply() { 
	float speedMult;
	float gravityMult;
	switch (rngEventActive) {
	case SPEEDUP:
		speedMult = gr_param->alterspeedAttrs.speedAlterAmount_fast;
		break;
	case SLOWDOWN: 
		speedMult = gr_param->alterspeedAttrs.speedAlterAmount_slow;
		break;
	default:
		return; // No change
	}
	for (int i = 0; i < 4; i++) {
		GOBJ* fighter = Fighter_GetGObj(i);
		if (fighter) {
			FighterData* fd = fighter->userdata;
			memcpy(&ogAttributes[i], &fd->attr, sizeof(attrReset));
			
			fd->attr.walk_initial_velocity *= speedMult;
			fd->attr.walk_acceleration *= speedMult;
			fd->attr.walk_maximum_velocity *= speedMult;
			fd->attr.slow_walk_max *= speedMult;
			fd->attr.mid_walk_point *= speedMult;
			fd->attr.fast_walk_min *= speedMult;

			fd->attr.dash_initial_velocity *= speedMult;
			fd->attr.dashrun_acceleration_a *= speedMult;
			fd->attr.dashrun_acceleration_b *= speedMult;
			fd->attr.dashrun_terminal_velocity *= speedMult;

			fd->attr.max_runbrake_frames /= speedMult;
			fd->attr.grounded_max_horizontal_velocity *= speedMult;
			fd->attr.jump_startup_time /= speedMult;
			fd->attr.jump_h_initial_velocity *= speedMult;
			fd->attr.jump_v_initial_velocity *= sqrtf(speedMult);

			fd->attr.ground_to_air_jump_momentum_multiplier *= sqrtf(speedMult);
			fd->attr.jump_h_max_velocity *= speedMult;
			fd->attr.hop_v_initial_velocity *= sqrtf(speedMult);
			fd->attr.air_jump_v_multiplier *= sqrtf(speedMult);
			fd->attr.air_jump_h_multiplier *= speedMult;

			fd->attr.terminal_velocity *= speedMult;
			fd->attr.aerial_drift_stick_mult *= speedMult;
			fd->attr.aerial_drift_base *= speedMult;
			fd->attr.aerial_drift_max *= speedMult;
			fd->attr.aerial_friction *= speedMult;
			fd->attr.fastfall_velocity *= speedMult;
			fd->attr.horizontal_air_mobility_constant *= speedMult;

			fd->attr.shield_break_initial_velocity *= speedMult;
			fd->attr.rebound_frames *= speedMult;

			fd->attr.ledge_jump_horizontal_velocity *= speedMult;
			fd->attr.ledge_jump_vertical_velocity *= sqrtf(speedMult);

			fd->attr.normal_landing_lag /= speedMult;
			fd->attr.n_air_landing_lag /= speedMult;
			fd->attr.f_air_landing_lag /= speedMult;
			fd->attr.b_air_landing_lag /= speedMult;
			fd->attr.u_air_landing_lag /= speedMult;
			fd->attr.d_air_landing_lag /= speedMult;

			fd->attr.wall_jump_horizontal_velocity *= speedMult;
			fd->attr.wall_jump_vertical_velocity *= sqrtf(speedMult);


			fd->attr.gravity *= speedMult;
		}
	}
	return;
}

void setAnimRate_allFighters(float rate) {
	for (int i = 0; i < 4; i++) {
		GOBJ* fighter = Fighter_GetGObj(i);
		if (fighter) {
			FighterData* fd = fighter->userdata;
			Fighter_SetAnimRate(fighter, rate);
		}
	}
}

void randEvent_speedAlter_onFrame() {
	if (rngEventActive == SPEEDUP) {
		setAnimRate_allFighters(gr_param->alterspeedAttrs.speedAlterAmount_fast);
	}
	else if (rngEventActive == SLOWDOWN) {
		setAnimRate_allFighters(gr_param->alterspeedAttrs.speedAlterAmount_slow);
	}
}

void randEvent_speedAlter_Kill() {
		// reset attributes
	for (int i = 0; i < 4; i++) {
		GOBJ* fighter = Fighter_GetGObj(i);
		if (fighter) {
			FighterData* fd = fighter->userdata;
			Fighter_SetAnimRate(fighter, 1.0f);
			memcpy(&fd->attr, &ogAttributes[i], sizeof(attrReset));
		}
	}
}