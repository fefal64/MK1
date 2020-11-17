// MTE MK1 v4.8
// Copyleft 2010, 2011, 2020 by The Mojon Twins

#ifdef PLAYER_PUSH_BOXES
	void move_tile (unsigned char act) {
		set_map_tile (x0, y0, 0, comportamiento_tiles [0]);
		set_map_tile (x1, y1, 14, comportamiento_tiles [14]);

		// Sound
		if (act) {
			play_sfx (8);
			#ifdef FALLING_BOXES
				// Añadir al buffer de cajas cayentes.
				fall_box ();
			#endif
		}
	}

	unsigned char can_move_box (void) {
		#ifdef ENEMIES_BLOCK_BOXES	
			boxx = x1 << 4; boyy = y1 << 4;
			rdd = enoffs + MAX_ENEMS;
			for (rdi = enoffs; rdi < rdd; rdi ++) {
				if (malotes [rdi].x >= boxx - 12 && malotes [rdi].x <= boxx + 12 &&
					malotes [rdi].y >= boyy - 12 && malotes [rdi].y <= boyy + 12) {
					play_sfx (9);
					return 0;
				}
			}
		#endif

		if (qtile (x0, y0) != 14 || attr (x1, y1) >= 4)
			return 0;

		#ifdef PUSH_OVER_FLOOR
			if (attr (x1, y1 + 1) < 4) return 0;
			if (qtile (x0, y0 - 1) == 14) return 0;
		#endif
			
		return 1;
	}

	#ifdef FALLING_BOXES
		void init_falling_box_buffer () {
			for (rdi = 0; rdi < MAX_FALLING_BOXES; rdi ++)
				fallingboxbuffer [rdi].act = 0;
		}

		void fall_box () {
			for (rdi = 0; rdi < MAX_FALLING_BOXES; rdi ++) {
				if (!fallingboxbuffer [rdi].act) {
					fallingboxbuffer [rdi].act = 1;
					fallingboxbuffer [rdi].x = x1;
					fallingboxbuffer [rdi].y = y1;
					break;
				}
			}
		}

		void animate_boxes () {
			// Only at the right time...
			fall_frame_counter ++;
			if (fall_frame_counter >= FALLING_BOXES_SPEED) {
				fall_frame_counter = 0;
				for (rdi = 0; rdi < MAX_FALLING_BOXES; rdi ++) {					
					if (fallingboxbuffer [rdi].act) {
						// Fall this box?
						if (attr (fallingboxbuffer [rdi].x, fallingboxbuffer [rdi].y + 1) < 4) {
							x0 = fallingboxbuffer [rdi].x; y0 = fallingboxbuffer [rdi].y;
							x1 = x0; y1 = y0 + 1;
							move_tile (0);

							// Check for cascades! (box above?)
							if (qtile (fallingboxbuffer [rdi].x, fallingboxbuffer [rdi].y - 1) == 14) {
								x1 = fallingboxbuffer [rdi].x; y1 = fallingboxbuffer [rdi].y - 1; 
								fall_box ();
							}
							
							fallingboxbuffer [rdi].y ++;
							
							#if defined (BOXES_KILL_ENEMIES) || defined (BOXES_KILL_PLAYER)
								boxx = fallingboxbuffer [rdi].x << 4;
								boyy = fallingboxbuffer [rdi].y << 4;
							#endif

							#ifdef BOXES_KILL_ENEMIES
								// Check for enemy killed!

								for (enit = 0; enit < MAX_ENEMS; enit ++) {
									enoffsmasi = enoffs + enit;
									
									#ifdef BOXES_ONLY_KILL_TYPE
										if (malotes [enoffsmasi].t == BOXES_ONLY_KILL_TYPE)
									#else
										if (malotes [enoffsmasi].t > 0 && malotes [enoffsmasi].t < 16)
									#endif
									{
										if (malotes [enoffsmasi].x >= boxx - 15 && malotes [enoffsmasi].x <= boxx + 15 &&
											malotes [enoffsmasi].y >= boyy - 15 && malotes [enoffsmasi].y <= boyy + 15) {
											
											#ifdef ENABLE_CODE_HOOKS
												enemy_died = malotes [enoffsmasi].t;
											#endif

											en_an_next_frame [enit] = sprite_17_a;											
											sp_MoveSprAbs (sp_moviles [enit], spritesClip, en_an_next_frame [enit] - en_an_current_frame [enit], VIEWPORT_Y + (malotes [enoffsmasi].y >> 3), VIEWPORT_X + (malotes [enoffsmasi].x >> 3), malotes [enoffsmasi].x & 7, malotes [enoffsmasi].y & 7);
											en_an_current_frame [enit] = en_an_next_frame [enit];
											sp_UpdateNow ();
											play_sfx (10);
											en_an_next_frame [enit] = sprite_18_a;
											malotes [enoffsmasi].t |= 16;			// Marked as "dead"

											// Count it
											player.killed ++;

											#ifdef ACTIVATE_SCRIPTING
												script = f_scripts [max_screens + 2];
												run_script ();
											#endif

											break;
										}
									}						
								}
							#endif

							#ifdef BOXES_KILL_PLAYER
								// Check for player killed!
								if (gpx >= boxx - 15 && gpx <= boxx + 15 && gpy >= boyy - 15 && gpy <= boyy + 15) {
									explode_player ();	
									player.life --;
									player.is_dead = 1;
								}
							#endif
						} else {
							fallingboxbuffer [rdi].act = 0;
						}
					}	
				}	
			}
		}
	#endif
#endif