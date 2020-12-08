// MTE MK1 v4.8
// Copyleft 2010, 2011, 2020 by The Mojon Twins

// pantallas.h
// Includes the binary of the aplib-compressed static screens.
// title.bin, marco.bin (if suited) and ending.bin should be
// in the same directory.

extern unsigned char s_title [];
extern unsigned char s_marco [];
extern unsigned char s_ending [];

#asm
	._s_title
		BINARY "title.bin"
	._s_marco
#endasm
#ifndef DIRECT_TO_PLAY
#asm
		BINARY "marco.bin"
#endasm
#endif
#asm
	._s_ending
		BINARY "ending.bin"
#endasm

void unpack (void) {
	#asm
			call blackout

			ld hl, (_asm_int)
			ld de, 16384
			jp depack

		.blackout
			ld hl, 22528
			ld de, 22529
			ld bc, 767
			xor a
			ld (hl), a
			ldir
			ret
	#endasm
}

void title_screen (void) {
	sp_UpdateNow();
	asm_int = (unsigned int) (s_title); unpack ();

	#asm
		; Music generated by beepola

		call musicstart

		#if !(defined MODE_128K_DUAL || defined MIN_FAPS_PER_FRAME)
			di
		#endif
	#endasm
	
	while (1) {
		if (sp_KeyPressed (key_1)) {
			joyfunc = sp_JoyKeyboard; break;
		} else if (sp_KeyPressed (key_2)) {
			joyfunc = sp_JoyKempston; break;
		} else if (sp_KeyPressed (key_3)) {
			joyfunc = sp_JoySinclair1; break;
		}			
	}
	
	after_title:
}

void game_ending (void) {
	sp_UpdateNow();
	asm_int = (unsigned int) (s_ending); unpack ();
	beepet (); play_sfx (11);
	espera_activa (500);
}

void game_over (void) {
	draw_rectangle (10, 11, 21, 13, GAME_OVER_ATTR);		
	draw_text (11, 12, GAME_OVER_ATTR, "GAME OVER!");
	sp_UpdateNow ();
	beepet (); play_sfx (10);
	espera_activa (500);
}
