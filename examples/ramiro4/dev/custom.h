// MTE MK1 v4.8
// Copyleft 2010, 2011, 2020 by The Mojon Twins

// Add here your custom routines & vars

#ifdef ENABLE_CODE_HOOKS

	#asm
		LIB SPPrintAtInv
	#endasm

	// Custom routines for Ramiro 4

	// bit 0 = which set.
	// bit 1 = killing eye.
	// bit 2 = trap!
	// bit 3 = trap but with coins
	unsigned char map_behaviours [] = {
		 0,  0,  0,  5,  0,  0, 
		 0,  0,  0,  3,  1,  1,
		 0,  0,  3,  3,  5,  1,
		13,  1,  1,  3,  3,  1,
		13,  1,  3,  1,  1,  1,
		 0,  1,  1,  1,  1,  1
	}; 

	// Evil eye things

	#define EYE_X VIEWPORT_X+7*2
	#define EYE_Y VIEWPORT_Y+2*2

	unsigned char evil_eye_state;
	unsigned char evil_eye_counter;

	unsigned char evil_eye_state_cts [] = { 30, 30, 60, 5, 5 };
	unsigned char evil_eye_state_tiles [] = { 29, 30, 31, 30, 29 };

	unsigned char evil_eye_screen;

	// Blocks trap

	#define MAX_TRAP_BLOCKS	3
	#define TRAP_CHANCE 	7 		// Power of two minus one!
	#define BLOCK_HIT 		5

	unsigned char trap_active;
	unsigned char trap_bx [MAX_TRAP_BLOCKS];
	unsigned char trap_by [MAX_TRAP_BLOCKS];
	unsigned char trap_bt [MAX_TRAP_BLOCKS];

	unsigned char trap_screen;
	unsigned char trap_coins;
	unsigned char _trap_bx;
	unsigned char _trap_by;
	unsigned char _trap_bt;
	unsigned char rda, rdb;

	// Coins trap extra stuff

	#define C_COINS_X 		9 		// Coins count character coordinates
	#define C_COINS_Y		23
	#define TRAP_COINS_MAX	30

	// Carrying an object

	unsigned char *object_cells [] = {
		0, extra_sprite_17_a, extra_sprite_18_a, extra_sprite_19_a, extra_sprite_20_a
	};
	unsigned char pinv;
	struct sp_SS *sp_pinv;
	unsigned char *pinv_next_frame, *pinv_current_frame;

	// Offers

	#define OFRENDAS_X 		15
	#define OFRENDAS_Y 		23
	unsigned char pofrendas, pofrendas_old; 
	unsigned char ofrendas_order [] = { 1, 2, 3, 4 };
	unsigned char ofrendas_idx;

	// Water trap

	#define WATER_PERIOD 20
	unsigned char water_level;
	unsigned char water_ct;
	unsigned char water_locks;
	unsigned char water_top_door_x;

	unsigned char water_pushplates [] = { 0, 0x26, 0x4D, 0x57, 0x79 };

	// Score 
	
	#define PSCORE flags[16]
	
	#define SCORE_OPEN_PYRAMID 		5
	#define SCORE_CHARACTER_TALK 	2
	#define SCORE_OPEN_CRYPT 		2
	#define SCORE_WIN_CRYPT 		5
	#define SCORE_RAMON_EYE 		5
	#define SCORE_RAMON_WATER 		5
	#define SCORE_GET_COIN 			5
	#define SCORE_GET_OBJECT 		5
	#define SCORE_FALSE_OBJECT 		4
	#define SCORE_FALSE_INTERACTION	4

	#define SCORE_X 		28
	#define SCORE_Y 		23

	unsigned char opscore;

	// Text

	unsigned char temp_string [] = "                        ";

	//                        XXXXXXXXXXXXXXXXXXXXXX
	unsigned char text0 [] = "POR OSIRIS Y POR APIS%"
							 "MIRADME BIEN: SOY EL%"
							 "ALTAR DE LAS OFRENDAS.%"
							 "TE DARE COSAS SI TRAES%"
							 "MONEDAS AL MENDA.";

	unsigned char text1 [] = "UN ROLLO DE PAPEL DEL%"
							 "CULO DOBLE CAPA, QUE%"
							 "TE DEJA SUAVITO Y TE%"
							 "QUITA LA ZURRAPA.";				 

	unsigned char text2 [] = "UNA FLAUTA DE FAKIR%"
							 "IMPORTADA DE ORIENTE%"
							 "QUE TE DUERME CON SU%"
							 "MUSICA O SI TE DA EN%"
							 "LOS DIENTES.";

	unsigned char text3 [] = "UNAS BRAGAS PRINCESA%"
							 "ROBADAS DE UN CAJON%"
							 "DE LA LETIZIA ESA.";

	unsigned char text4 [] = "UN TARRO DE GRASA DE%"
							 "CABALLO. PARA QUE%"
							 "QUERRIAS ESTO? LOCO%"
							 "ME HALLO.";

	unsigned char text5 [] = "TES KI YA CARAJAULA,%"
							 "LLEVATE ESO!";

	unsigned char text6 [] = "Y ESTO QUE ES? BEBE-%"
							 "CHARCOS, ESCUCHAPEOS";

	unsigned char text7 [] = "PARA QUE QUIERO ESTO,%"
							 "BOQUIMUELLE?";

	unsigned char text8 [] = "PERO QUE ME TRAES?%"
							 "BOTARATE TALLOCEBOLLA!";

	unsigned char text9 [] = "Y AY, QUE POCAS LUCES%"
							 "ME DUELE LA PETACA.%"
							 "COMI MUCHAS CHUCHES%"
							 "Y ME HAGO MUCHA CACA.";

	unsigned char text10 [] = "AUNQUE SEA DENOCHE%"
							  "NO CONSIGO DORMIR.%"
							  "TENGO MUCHO INSOMNIO%"
							  "QUE PUEDO HACIR?";

	unsigned char text11 [] = "QUE DESPISTE TENGO%"
							  "AYER FUI LO PEOR. ME%"
							  "DESMADRE EN UN CUMPLE%"
							  "Y PERDI LA ROPA%"
							  "INTERIOR.";

	unsigned char text12 [] = "ESTOY SIN RECATO%"
							  "A SU SERVICIO.%"
							  "TRABAJO MUY BARATO%"
							  "PERO EL CUERO ES MI%"
							  "VICIO...";

	unsigned char text13 [] = "RECUPERA LOS CUATRO%"
							  "TROZOS DEL PAPIRO%"
							  "Y VUELVE AQUI PARA%"
							  "HACER EL HECHIZO";

	unsigned char text14 [] = "VAYA INSISTENCIA, TE%"
							  "ABRO MI PIRAMIDE,%"
							  "MONTUNO! QUE CASI PA-%"
							  "RECES EL REY DE LOS%"
							  "HUNOS!";

	unsigned char text15 [] = "LO CONSIGUIO AL FIN!%"
							  "ENSAMBLADO EL PAPIRO%"
							  "SE DISPONE A LEER EL%"
							  "CONJURO NUESTRO BUEN%"
							  "RAMIRO.";

	unsigned char text16 [] = "DICE ASI:%"
							  "- 2 CEBOLLAS%"
							  "- PAPEL DEL CULO%"
							  "- PAN%"
							  "- FAIRY";

	unsigned char text17 [] = "EL POBRE VAMPIRO SE%"
							  "QUEDA CON CARA MONA:%"
							  "NO ES UN CONJURO,%"
							  "ES LA LISTA DEL%"
							  "MERCADONA.";

	unsigned char text18 [] = "YA QUE ME TRAES UNA%"
							  "OFRENDA, YO SOLTARE%"
							  "PRENDA...";

	unsigned char text19 [] = "HAZ BUEN USO DE LO%"
							  "QUE TE HE DADO!";

	unsigned char text20 [] = "Y YA TE ABRI. AHORA%"
							  "JUYE... JUYE!!";

	unsigned char text21 [] = "OH, QUE SUAVE ES!%"
							  "Y AHORA, PORFA, VETE%"
							  "QUE HARE CACA Y ME%"
							  "LIMPIARE EL OJETE";

	unsigned char text22 [] = "UNA FLAUTA DE FAKIR!%"
							  "CON FEO SU SONIDO%"
							  "EN SOLO UNOS MITUTOS%"
							  "YA ESTARE DORMIDO";

	unsigned char text23 [] = "OH, GUAPO VAMPIRILLO,%"
							  "RECIBO CON ALBOROTO%"
							  "TU BELLO REGALO: UNAS%"
							  "BRAGAS PA MI TOTO";

	unsigned char text24 [] = "QUE LUSTROSO QUEDARA%"
							  "EL CUERO DE MI ARNES%"
							  "IRE VISITAR A MARISA%"
							  "A CHUPARLE LOS PIES";

	unsigned char text25 [] = "SI SACAS LA MONEDA%"
							  "ENFADARAS A HORUS!%"
							  "YA SOLO TE QUEDA%"
							  "RASCARLE LOS OJUS!";

	unsigned char text26 [] = "SOY SONIA LA MOMIA%"
							  "GUARDIANA DE LA%"
							  "TERCERA CRIPTA";

	unsigned char text27 [] = "SOY CLIEMENTE LA%"
							  "SERPIENTE,%"
							  "GUARDIAN DE LA%"
							  "CUARTA CRIPTA";

	unsigned char text28 [] = "SOY MARISA LA%"
							  "SACERDOTISA,%"
							  "GUARDIANA DE LA%"
							  "SEGUNDA CRIPTA";

	unsigned char text29 [] = "SOY GUSTAVO EL%"
							  "ESCLAVO,%"
							  "GUARDIAN DE LA%"
							  "PRIMERA CRIPTA";

	unsigned char text30 [] = "LOS TROZOS ESTAN%"
							  "EN CRIPTAS CERRADAS,%"
							  "TENDRAS QUE COMPLACER%"
							  "A SUS GUARDIANES";

	unsigned char text31 [] = "\"TE PILLE, LORITO!\",%"
							  "OYES A ALGUIEN GRITAR%"
							  "\"NO PIERDAS TU PORTE%"
							  "Y VUELVE A EMPEZAR!\"";

	unsigned char text32 [] = "CUIDADO CON EL OJO!%"
							  "SE HACE LA DORMIDA%"
							  "PERO SI TE VE%"
							  "TE CHUPA LA VIDA!";

	unsigned char text33 [] = "RAMON EL FARAON,%"
							  "TE INVITO A SU KELI%"
							  "Y ENTRE VINOS Y HUMO%"
							  "TE CONTO SU PELI...";

	unsigned char text34 [] = "SI JUNTAS 4 PARTES%"
							  "EL PODEWR DEL PAPIRO%"
							  "OCULTO EN ESTE SITIO%"
							  "SERA TUYO, RAMIRO";

	unsigned char text35 [] = "BUSCA A RAMON Y QUE%"
							  "CON SU ABRACADABRA%"
							  "NO SE HAGA EL REMOLON%"
							  "Y LA PIRAMIDE TE ABRA";

	unsigned char *texts [] = {
		text0, 								// Bienvenida altar
		text1, text2, text3, text4, 		// Altar describe objetos
		text5, text6, text7, text8, 		// Guardianes mosqueados
		text9, text10, text11, text12, 		// Presentación guardianes
		text13, 							// Puedes pasar
		text14, 							// Ramón el faraón
		text15, text16, text17,				// Final
		text18, text19,						// Más mensajes del altar
		text20, 							// Ya te abrí.
		text21, text22, text23, text24,		// Gracias por el objeto
		text25,								// Cisterna
		text26, text27, text28, text29, 	// Guardian de...
		text30,								// Tendras que complacer
		text31,								// Te pillé!
		text32, 							// Advertencia Ramón
		text33, text34, text35 				// Intro
	};

	unsigned char talk_sounds [] = { 7, 11 };
	unsigned char redraw_after_text = 0;

	// Admiration signs (!)
	// Coordiantes are screen-absolute, precalculated.
	unsigned char adm_s_n_pant [] = {  0,  2,  5, 10, 13, 14, 19, 25};
	unsigned char adm_s_x [] =      {  6, 20, 22, 16, 20,  6,  6,  6};
	unsigned char adm_s_y [] =      { 12, 14, 16, 10, 16, 16,  4,  4};

	// Aux. functions

	void clear_gamearea (void) {
		// Tints game area black
		#asm
				ld  hl, 22528 + 64
				ld  de, 22528 + 65
				ld  bc, 767 - 128
				xor a
				ld  (hl), a
				ldir
		#endasm
	}

	void paint_water_strip (void) {
		// Paints a strip of character rda at rdy
		#asm
				ld  a, (_rdy)
				cp  VIEWPORT_Y+20
				ret nc 						// Do not paint if rdy >= 20.

				ld  c, VIEWPORT_X+2
				call SPCompDListAddr
				
				// Now we have to write 30 chars
				ld  b, 26
				ld  a, (_rdi) 				// Which char
				ld  c, 5 					// Colour
			
			.paint_water_strip_loop
				ld  (hl), c 				// Paint colour
				inc hl

				ld  (hl), a
				inc hl

				inc hl
				inc hl

				djnz paint_water_strip_loop

				// Now invalidate
				ld  c, VIEWPORT_X
				ld  e, VIEWPORT_X + 29
				ld  a, (_rdy)
				ld  b, a
				ld  d, a
				ld  iy, fsClipStruct
				call SPInvalidate
		#endasm
	}

	void draw_falling_block (void) {
		//draw_coloured_tile (VIEWPORT_X + (_trap_bx << 1), VIEWPORT_Y + (_trap_by << 1), _trap_bt);
		
		#asm
			ld  a, (__trap_bx)
			sla a
			add VIEWPORT_X
			ld  (__x), a

			ld  a, (__trap_by)
			sla a
			add VIEWPORT_Y
			ld  (__y), a
		
			ld  a, (__trap_bt)
			ld  (__t), a

			jp _draw_coloured_tile_do	
		#endasm
	}

	void clear_temp_string (void) {
		#asm
				ld  hl, _temp_string
				ld  de, _temp_string+1
				ld  bc, 23
				ld  a, 32
				ld  (hl), a
				ldir
		#endasm
	}

	void redraw_from_buffer (void) {
		#asm
				ld  a, VIEWPORT_X
				ld  (__x), a
				ld  a, VIEWPORT_Y
				ld  (__y), a
				
				xor a
			.redraw_from_buffer_loop
				ld  (_gpit), a

				ld  bc, (_gpit)
				ld  b, 0
				ld  hl, _map_buff
				add hl, bc
				ld  a, (hl)
				ld  (__t), a

				call _draw_coloured_tile_do

				ld  a, (__x)
				add a, 2
				cp  VIEWPORT_X + 30
				jr  nz, redraw_from_buffer_set_x
				ld  a, (__y)
				add a, 2
				ld  (__y), a
				ld  a, VIEWPORT_X
			.redraw_from_buffer_set_x
				ld  (__x), a

				ld  a, (_gpit)
				inc a
				cp  150
				jr  nz, redraw_from_buffer_loop
		#endasm
	}

	void sprite_remove_aid (void) {
		saca_a_todo_el_mundo_de_aqui ();
		// sp_MoveSprAbs (sp_pinv, spritesClip, 0, 20+VIEWPORT_Y, 30+VIEWPORT_X, 0, 0);
		#asm
				ld  ix, (_sp_pinv)
				ld  iy, vpClipStruct
				ld  bc, 0
				ld  hl, 0xfefe	// -2, -2
				ld  de, 0
				call SPMoveSprAbs
		#endasm
		
		// Validate whole screen so sprites stay on next update
		#asm
				LIB SPValidate
				ld  c, VIEWPORT_X
				ld  b, VIEWPORT_Y
				ld  d, VIEWPORT_Y+19
				ld  e, VIEWPORT_X+29
				ld  iy, fsClipStruct
				call SPValidate
		#endasm				
	}

	void decorate_screen (void) {
		// Admiration (!)
		rdi = 0;
		while (adm_s_n_pant [rdi] <= n_pant) {			
			if (adm_s_n_pant [rdi] == n_pant) {
				draw_coloured_tile (adm_s_x [rdi], adm_s_y [rdi], 49);
				break;
			}
			rdi ++;
		}

		// Paint evil eye
		if (evil_eye_screen) {
			draw_coloured_tile (EYE_X-2, EYE_Y, 28);
			draw_coloured_tile (EYE_X, EYE_Y, 29);
		}
	}

	void show_text_box (unsigned char n) {
		sprite_remove_aid ();

		gp_gen = texts [n];

		// Text renderer will read the string and
		// build substrings for draw_text.

		//clear_temp_string ();
		draw_text (4, 6, 40, temp_string);
		rdy = 7;

		while (1) {
			#asm
					// Fill buffer
					ld  de, _temp_string + 1
					ld  hl, (_gp_gen)

				.fill_buffer_loop
					ld  a, (hl)
					or  a
					jr  z, fill_buffer_end
					cp  '%'
					jr  z, fill_buffer_end

					ld  (de), a

					inc hl
					inc de
					jr  fill_buffer_loop

				.fill_buffer_end
					ld  (_gp_gen), hl
			#endasm

			draw_text (4, rdy ++, 40, temp_string);
			clear_temp_string ();
			draw_text (4, rdy ++, 40, temp_string);

			sp_UpdateNow ();
			play_sfx (talk_sounds [rand () & 1]);

			#ifdef MODE_128K_DUAL
				if (is128k) {
					#asm
							ld  b, 20
						.textbox_delay
							halt
							djnz textbox_delay
					#endasm
				}
			#endif
		
			if (*gp_gen == 0) break;
			gp_gen ++;
		}

		while (any_key ()); while (!any_key ()); 
		if (redraw_after_text) {
			redraw_from_buffer ();
			hotspot_paint ();
			decorate_screen ();
			render_all_sprites ();
		}
		redraw_after_text = 1;
	}

	void recuadrius (void) {	
		sprite_remove_aid ();			
		for (rdi = 0; rdi < 10; rdi ++) {
			for (rdx = rdi; rdx < 30 - rdi; rdx ++) {
				#asm
						// sp_PrintAtInv (VIEWPORT_Y + rdi, VIEWPORT_X + rdx, 71, 0);
						ld  de, 0x4700
						ld  a, (_rdx)
						add VIEWPORT_X
						ld  c, a
						ld  a, (_rdi)
						add VIEWPORT_Y
						call SPPrintAtInv
					
						// sp_PrintAtInv (VIEWPORT_Y + 19 - rdi, VIEWPORT_X + rdx, 71, 0);
						ld  de, 0x4700
						ld  a, (_rdx)
						add VIEWPORT_X
						ld  c, a
						ld  a, (_rdi)
						ld  b, a
						ld  a, VIEWPORT_Y + 19
						sub b
						call SPPrintAtInv
				#endasm

				if (rdx < 19 - rdi) {
					#asm
							// sp_PrintAtInv (VIEWPORT_Y + rdx, VIEWPORT_X + rdi, 71, 0);
							ld  de, 0x4700
							ld  a, (_rdi)
							add VIEWPORT_X
							ld  c, a
							ld  a, (_rdx)
							add VIEWPORT_Y
							call SPPrintAtInv

							// sp_PrintAtInv (VIEWPORT_Y + rdx, VIEWPORT_X + 29 - rdi, 71, 0);
							ld  de, 0x4700
							ld  a, (_rdi)
							ld  b, a
							ld  a, VIEWPORT_X + 29
							sub b
							ld  c, a
							ld  a, (_rdx)
							add VIEWPORT_Y							
							call SPPrintAtInv
					#endasm
				}
			}
			#asm
				halt
			#endasm
			sp_UpdateNow (0);
		}
	}

	void trap_kill (void) {
		sp_UpdateNow ();
		play_sfx (10);

		#ifdef MODE_128K_DUAL
			if (is128k) {
				#asm
						ld  b, 50
					.trap_kill_delay
						halt
						djnz trap_kill_delay
				#endasm
			}
		#endif
		
		if (is128k) arkos_play_music (5);
		show_text_box (31);
		sp_UpdateNow ();
		
		player.life -= BLOCK_HIT; 
		player.estado = EST_PARP;
		player.ct_estado = 50;
		player.vy = 0;
		recuadrius ();
	}

	void water_trap_setup (void) {
		rdi = n_pant / 6;

		// Paint top
		if (rdi > 0) {
			water_top_door_x = (rdi & 1) ? 11 : 2;
			set_map_tile (water_top_door_x, 0, 6, 8);
			set_map_tile (water_top_door_x + 1, 0, 7, 8);

			rdx = water_pushplates [rdi];
			set_map_tile (rdx >> 4, 0, 19, 8);
			set_map_tile (rdx & 15, 0, 19, 8);
		}

		// Paint bottom 
		if (rdi < 4) {
			rdx = (rdi & 1) ? 2 : 11;
			set_map_tile (rdx, 9, 46, 4);
			set_map_tile (rdx + 1, 9, 46, 4);
		}

		water_locks = 0;
	}

	// Hooks

	void hook_system_inits (void) {
		sp_pinv = sp_CreateSpr (sp_MASK_SPRITE, 3, sprite_2_a, 3);
		sp_AddColSpr (sp_pinv, sprite_2_b);
		sp_AddColSpr (sp_pinv, sprite_2_c);
		pinv_current_frame = pinv_next_frame = sprite_2_a;
	}

	void hook_init_game (void) {
		water_level = 0; 
		pinv = 0;
		ofrendas_idx = 0;
		pofrendas = 0;
		pofrendas_old = 0xff;
		PSCORE = 0;
		opscore = 0xff;
		
		/*
		flags [6] = 1; 
		pinv = 4; pinv_next_frame = object_cells [pinv];
		gpx = 160; player.x = 160<<6;
		*/
		
		#asm
				ld b, 4
				ld a, r 
				ld (_seed), a

			.shuffle_loop
				push bc
				call _rand
				pop  bc
				ld  a, l
				and 3
				ld  c, a
				push bc
				call _rand
				pop  bc
				ld  a, l
				and 3
				ld  d, 0
				ld  e, a
				ld  hl, _ofrendas_order
				add hl, de
				ld  a, (hl)
				ld  (_rdi), a
				ld  e, c
				push hl
				ld  hl, _ofrendas_order
				add hl, de
				ld  a, (hl)
				pop hl
				ld  (hl), a
				ld  a, (_rdi)
				ld  hl, _ofrendas_order
				add hl, de
				ld  (hl), a
				
				djnz shuffle_loop
		#endasm

		if (is128k) arkos_play_music (1);
	}

	void hook_init_mainloop (void) {
	}

	void hook_mainloop (void) {

		// Eye of horus

		if (evil_eye_screen) {
			if (evil_eye_counter) {
				evil_eye_counter --;
			} else {
				evil_eye_state ++; if (evil_eye_state == 5) evil_eye_state = 0;
				evil_eye_counter = evil_eye_state_cts [evil_eye_state];
				draw_coloured_tile (EYE_X, EYE_Y, evil_eye_state_tiles [evil_eye_state]);
				scenery_info.evil_zone_active = (evil_eye_state == 2);
			}
		}

		sp_Border ((scenery_info.evil_zone_active & half_life) ? 2 : 0);

		// Block trap

		// To make trap active, we detect the player got a new obj.
		if (trap_screen && player.objs != objs_old) {
			if (is128k) arkos_stop_sound ();
			flags [10 + flags [15]] = 1;
			trap_active = 1;
			seed = n_pant + 1;
			player.life += BLOCK_HIT;
			scenery_info.allow_type_6 = 1;
			flags [COIN_FLAG] = 0;
			#asm
					ld  hl, _trap_by
					ld  de, _trap_by + 1
					ld  bc, MAX_TRAP_BLOCKS - 1
					ld  a, 0xff
					ld  (hl), a
					ldir
			#endasm
			if (trap_coins) {
				set_map_tile (13, 5, 0, 0);
				sp_UpdateNow ();
				play_sfx (10);
			}
			if (is128k) arkos_play_music (2);
		}

		if (trap_active) {
			
			// throw a new block
			if ((rand () & TRAP_CHANCE) == 1) { 
				#asm
						ld  bc, MAX_TRAP_BLOCKS
					.trap_block_find_loop
						dec c
						ld  hl, _trap_by
						add hl, bc
						ld  a, (hl)
						cp  0xff
						jr  z, trap_block_create_new

						xor a
						or  c
						jr  z, trap_block_find_done
						jr  trap_block_find_loop

					.trap_block_create_new
						xor a
						ld  (hl), a

						push bc
					.trap_block_select_x
						call _rand

						ld  a, l
						and 0xf
						jr  z, trap_block_select_x
						cp  14
						jr  nc, trap_block_select_x
						pop bc

						ld  hl, _trap_bx
						add hl, bc
						ld  (hl), a

						ld  a, (_trap_coins)
						or  a
						jr  nz, trap_block_set_coins

						push bc
						call _rand
						pop bc
						
						ld  a, l
						and 1
						add 6
						jr  trap_block_write

					.trap_block_set_coins
						ld  a, 50

					.trap_block_write
						ld  hl, _trap_bt
						add hl, bc
						ld  (hl), a

					.trap_block_find_done
				#endasm
			}

			// Animate
			if (half_life) {
				for (gpit = 0; gpit < MAX_TRAP_BLOCKS; gpit ++) {

					#asm
							ld  bc, (_gpit)
							ld  b, 0

							ld  hl, _trap_by
							add hl, bc
							ld  a, (hl)
							ld  (__trap_by), a

							ld  hl, _trap_bx
							add hl, bc
							ld  a, (hl)
							ld  (__trap_bx), a

							ld  hl, _trap_bt
							add hl, bc
							ld  a, (hl)
							ld  (__trap_bt), a
					#endasm
					
					if (_trap_by != 0xff) {
						rda = _trap_bx + (_trap_by << 4) - _trap_by;

						// Make fall
						if (_trap_by)				
							set_map_tile (_trap_bx, _trap_by, map_buff [rda], 0);
						
						_trap_by ++; rda += 15;

						rdx = (gpx + 8) >> 4; rdy = (gpy + 8) >> 4;

						if (rdx == _trap_bx && rdy == _trap_by && trap_coins) {
							flags [COIN_FLAG] ++;
							play_sfx (5);
							player.life += COINS_REFILL;
							_trap_by = 0xff;
						} else if (map_attr [rda] == 1) {
							_trap_by = 0xff;
						} else {
							draw_falling_block ();
						
							if (map_attr [rda + 15] & 12) {
								if (rdx == _trap_bx && rdy == _trap_by) {
									//if (player.estado != EST_PARP) {
										// Crushed!
										trap_kill ();

										// Reenter & reset
										hotspots [n_pant].act = 1;
										player.objs --;
										on_pant = 0xff;
										flags [10 + flags [15]] = 0;
										break;
									/*
									} else {
										player.y -= 16<<6;
									}
									*/
								}
								map_attr [rda] = comportamiento_tiles [_trap_bt];
								map_buff [rda] = _trap_bt;
								_trap_by = 0xff; 
							}

						}

						trap_by [gpit] = _trap_by;

						// Finally
						if (flags [COIN_FLAG] == TRAP_COINS_MAX) {
							// Deativate trap!
							scenery_info.allow_type_6 = 0;
							play_sfx (8);
							trap_active = 0;
							if (is128k) arkos_stop_sound ();
							draw_scr_background ();
							if (is128k) arkos_play_music (1);
						} 
					}
				}
			}
		}

		// Carrying object
		if (pinv) {
			if (player.facing) rdx = gpx - 4; else rdx = gpx + 4;
			rdy = gpy - 4;
		} else rdx = 240;

		/*
		sp_MoveSprAbs (sp_pinv, spritesClip, pinv_next_frame - pinv_current_frame, 
			VIEWPORT_Y + (rdy >> 3), VIEWPORT_X + (rdx >> 3), rdx & 7, rdy & 7);
		*/
		#asm
				ld  ix, (_sp_pinv)
				ld  iy, vpClipStruct

				ld  hl, (_pinv_next_frame)			// player.next_frame
				ld  de, (_pinv_current_frame) 			// player.current_frame
				or  a
				sbc hl, de
				ld  b, h
				ld  c, l

				ld  a, (_rdy)
				srl a
				srl a
				srl a
				add VIEWPORT_Y
				ld  h, a 

				ld  a, (_rdx)
				srl a
				srl a
				srl a
				add VIEWPORT_X
				ld  l, a 
				
				ld  a, (_rdx)
				and 7
				ld  d, a

				ld  a, (_rdy)
				and 7
				ld  e, a

				call SPMoveSprAbs
		#endasm

		pinv_current_frame = pinv_next_frame;

		// Offers
		if (latest_hotspot == 2) {
			pofrendas ++;
			play_sfx (5);
			
			// Activate water trap
			if (n_pant == 29) {
				water_level = 25;
				water_trap_setup ();
				if (is128k) arkos_play_music (2);
			}

			PSCORE += SCORE_GET_COIN;
		}

		if (pofrendas != pofrendas_old) {
			draw_2_digits (OFRENDAS_X, OFRENDAS_Y, pofrendas);
			pofrendas_old = pofrendas;
		}

		if (flags [COIN_FLAG] != coins_old) {
			draw_2_digits (C_COINS_X, C_COINS_Y, TRAP_COINS_MAX - flags [COIN_FLAG]);
			coins_old = flags [COIN_FLAG];
		}

		if (PSCORE != opscore) {
			draw_2_digits (SCORE_X, SCORE_Y, PSCORE);
			opscore = PSCORE;
		}

		// Water level
		if (water_level) {

			// Move water
			if (water_ct) water_ct --; else {
				water_level --;
				rdy = water_level + VIEWPORT_Y; rdi = 62; paint_water_strip ();
				rdy ++; rdi = 63; paint_water_strip ();
				water_ct = WATER_PERIOD;
			}

			// Detect collision
			if (gpy <= 144 && (water_level << 3) <= gpy) {
				trap_kill ();

				// Reset trap!
				water_level = 0;
				hotspots [29].act = 1;
				pofrendas --;
				n_pant = 5;
				gpy = player.y = 0;
				gpx = 120; player.x = 120<<6;
				if (is128k) arkos_play_music (1);				
			}

			// Detect horus tiles
			rdx = (gpx + 8) >> 4; rdy = (gpy - 2) >> 4;
			if (player.ceiling && qtile (rdx, rdy) == 19) {
				water_locks ++;
				set_map_tile (rdx, rdy, 11, 8);
				sp_UpdateNow ();
				play_sfx (5);
				if (water_locks == 2) {
					// Open trap!
					set_map_tile (water_top_door_x, 0, 0, 0);
					set_map_tile (water_top_door_x + 1, 0, 0, 0);
					sp_UpdateNow ();
					play_sfx (8);
				}
			}
		}

		// Intro 
		if (n_pant == 12 && flags [5] == 0 && player.possee) {
			flags [5] = 1;
			render_all_sprites (); 
			sp_UpdateNow ();
			do_extern_action (2);
		}
	}

	void hook_entering (void) {		
		/*
		evil_eye_screen = map_behaviours [n_pant] & 2;
		trap_screen = map_behaviours [n_pant] & 4;
		trap_coins = map_behaviours [n_pant] & 8;
		*/
		#asm
				ld  bc, (_n_pant)
				ld  b, 0
				ld  hl, _map_behaviours
				add hl, bc
				ld  c, (hl)

				ld  a, c
				and 2
				ld  (_evil_eye_screen), a

				ld  a, c
				and 4
				ld  (_trap_screen), a

				ld  a, c
				and 8
				ld  (_trap_coins), a		
		#endasm

		scenery_info.evil_zone_active = 0;
		scenery_info.allow_type_6 = 0;

		// Paint eye and admiration bubbles
		decorate_screen ();

		evil_eye_state = 2;
		evil_eye_counter = 0;

		if (trap_active) {
			if (is128k) arkos_play_music (1);
			PSCORE += SCORE_WIN_CRYPT;
		} 
		trap_active = 0;

		// Water level:
		if (water_level) {
			player.vy = -PLAYER_MAX_VY_SALTANDO;
			water_trap_setup ();
			
			if (n_pant == 5) {
				water_level = 0;
				if (is128k) arkos_play_music (1);
			} else water_level = 25;
		}

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
