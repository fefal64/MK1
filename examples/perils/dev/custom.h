// MTE MK1 v4.8
// Copyleft 2010-2013, 2020-2021 by The Mojon Twins

// Add here your custom routines & vars

// Comment this to remove the "next level" cheat
#define ENABLE_CHEAT

unsigned char resonators_on;
unsigned char player_min_killable;

unsigned char level, new_level;
unsigned char new_level_string [] = "LEVEL 00";

unsigned char scr_ini [] = { 60, 64, 71 };
unsigned char ini_x [] = { 1, 1, 11 };
unsigned char ini_y [] = { 4, 4, 4 };

unsigned char tilemaps [] = {
	 0,  1,  2,  3, 25,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
	32, 33, 34, 11, 36, 37, 38, 39, 40, 41, 12, 23, 24, 45,  0, 15,
	 0, 17, 46, 47, 43, 44, 35,  6, 26,  9, 19, 22, 27, 39, 25, 15
};

unsigned char continue_on;

// Custom functions

void paralyze_everyone (void) {
	player_min_killable = 0;
	for (enit = 0; enit < 3; enit ++) {
		en_an_count [enit] = 0xff;
		en_an_state [enit] = ENEM_PARALYZED;
	}
}

void restore_everyone (void) {
	player_min_killable = 4;
	for (enit = 0; enit < 3; enit ++) {
		en_an_count [enit] = 0;
		en_an_state [enit] = 0;
	}
}

/*
void set_hotspot (unsigned char hn) {
	hotspots [n_pant].act = 1;
	hotspot_t = hn;
	hotspots [n_pant].tipo = hotspot_t;
	rdx = (hotspots [n_pant].xy >> 4);
	rdy = (hotspots [n_pant].xy & 15);
	hotspot_x = rdx << 4;
	hotspot_y = rdy << 4;
	set_map_tile (rdx, rdy, 16 + hn, 0);
}
*/


void set_hotspot (unsigned char hn) {
	// Hotspot structure is xy, tipo, act.
	hotspot_t = hn;

	#asm
		// First, make a pointer to hotspots [n_pant]
			ld  a, (_n_pant)
			ld  b, a
			sla a 				// x2
			add a, b  			// x3
			ld  c, a
			ld  b, 0
			ld  hl, _hotspots
			add hl, bc

		// We'll be using xy and modifying tipo and act.
			ld  c, (hl)			// C = xy
			inc hl				// now HL points to tipo

		// hotspots [n_pant].tipo = hotspot_t;
			ld  a, (_hotspot_t)
			ld  (hl), a
			inc hl 				// now HL points to act

		// hotspots [n_pant].act = 1;
			ld  a, 1
			ld  (hl), a

		// rdx = (hotspots [n_pant].xy >> 4);
			ld  a, c
			srl a
			srl a
			srl a
			srl a
			ld  (_rdx), a
		
		// hotspot_x = rdx << 4;
			ld  a, c
			and 0xf0
			ld  (_hotspot_x), a

		// rdy = (hotspots [n_pant].xy & 15);
			ld  a, c
			and 15
			ld  (_rdy), a
		
		// hotspot_y = rdy << 4;
			sla a
			sla a
			sla a
			sla a
			ld  (_hotspot_y), a
	#endasm

	set_map_tile (rdx, rdy, 16 + hn, 0);
}

#ifdef ENABLE_CODE_HOOKS

	// Hooks

	void hook_system_inits (void) {
		continue_on = 0;
		level = 0;
	}

	void hook_init_game (void) {
		resonators_on = 0;
		player_min_killable = 4;
		new_level = 1;
		//player.keys = 1;
	}

	void hook_init_mainloop (void) {

		#ifdef ENABLE_CHEAT
			if (sp_KeyPressed (key_1) && sp_KeyPressed (key_3)) {
				player.killed = 60;
			}
		#endif

		if (player.killed == 60) {
			level ++;
			if (level < 3) {
				new_level = 1;
			} else {
				game_loop_flag = 1;
			}
		}

		if (new_level) {
			saca_a_todo_el_mundo_de_aqui ();
			new_level = 0;
			sp_ClearRect (spritesClip, 0, 0, sp_CR_TILES);
			sp_Invalidate (spritesClip, spritesClip);
			new_level_string [7] = level + '1';
			draw_text (12, 11, 71, new_level_string);
			draw_text (11, 13, 71, "KICK ASSES");
			sp_UpdateNow ();
			play_sfx (10);
			espera_activa (150);
			n_pant = scr_ini [level];
			init_player_values ();
			player.killed = 0; 
			resonators_on = 0;
			tileset_mappings = (unsigned char *) (tilemaps + (level << 4));
		}
	}

	void hook_mainloop (void) {
		if (latest_hotspot >= 4) {
			// Check 
			if (latest_hotspot == 4
				&& player.vy > 0
				&& gpy + 8 <= hotspot_y
			) {
				play_sfx (6);
				resonators_on = 250;
				latest_hotspot = 5;
				paralyze_everyone ();
				player.vy = -PLAYER_MAX_VY_SALTANDO;
			}

			// Hotspot has to be restored ALWAYS
			set_hotspot (latest_hotspot);			
		}

		if (resonators_on) {
			rdi = resonators_on / 25;
			resonators_on --;
			rdd = resonators_on / 25;
			if (rdi != rdd) {
				play_sfx (4);
				draw_2_digits (25, 1, rdd);
			}

			if (resonators_on == 0) {
				play_sfx (3);
				restore_everyone ();				
				if (hotspot_t >= 4) set_hotspot (4);
			}
		} 
	}

	void hook_entering (void) {
		// Modify hotspots upon resonators_on
		if (hotspot_t >= 4) {
			set_hotspot (resonators_on ? 5 : 4);			
		}
				
		if (resonators_on) paralyze_everyone ();
	}

#endif

#ifdef ENABLE_CUSTOM_ENEMS

	void extra_enems_init (void) {
	}

	void extra_enems_move (void) {		
	}

	void extra_enems_checks (void) {
	}

	void extra_enems_killed (void) {
	}
	
#endif
