
; Tabla de instrumentos
TABLA_PAUTAS: DW PAUTA_0,PAUTA_1,PAUTA_2,PAUTA_3,PAUTA_4,PAUTA_5,0,PAUTA_7,PAUTA_8,PAUTA_9,PAUTA_10,PAUTA_11,PAUTA_12,PAUTA_13,PAUTA_14,PAUTA_15,PAUTA_16

; Tabla de efectos
TABLA_SONIDOS: DW SONIDO0,SONIDO1,SONIDO2,SONIDO3,SONIDO4,SONIDO5,SONIDO6,SONIDO7,SONIDO8,SONIDO9

;Pautas (instrumentos)
;Instrumento 'Piano'
PAUTA_0:	DB	8,0,7,0,6,0,5,0,129
;Instrumento 'Piano Reverb'
PAUTA_1:	DB	11,0,12,0,11,0,10,0,9,0,9,0,9,0,9,0,9,0,9,0,8,0,8,0,8,0,8,0,136
;Instrumento 'Fade In FX'
PAUTA_2:	DB	2,0,3,0,4,8,4,-1,5,-4,5,20,5,-24,4,4,132
;Instrumento 'Guitar 1'
PAUTA_3:	DB	15,0,15,0,13,0,13,0,11,0,10,1,10,1,10,-1,9,-1,9,0,9,0,134
;Instrumento 'Guitar 2'
PAUTA_4:	DB	13,0,13,0,12,0,11,0,9,0,8,1,8,0,8,0,8,-1,8,0,8,0,134
;Instrumento 'Eco guitar'
PAUTA_5:	DB	7,0,7,0,7,0,6,0,6,0,6,0,6,0,6,0,5,0,5,0,5,0,5,0,5,0,4,0,4,0,4,0,4,0,3,0,0,0,129
;Instrumento 'Solo Guitar'
PAUTA_7:	DB	76,0,11,0,11,0,11,0,10,0,9,1,9,0,9,-1,9,0,9,0,9,-1,9,0,9,1,9,0,9,0,138
;Instrumento 'Eco Solo Guitar'
PAUTA_8:	DB	70,0,6,0,6,0,5,0,5,0,5,0,5,0,5,0,4,0,4,0,4,0,4,0,4,0,4,0,3,0,3,0,3,0,3,0,3,0,3,0,2,0,2,0,2,0,1,0,129
;Instrumento 'Slap Bass'
PAUTA_9:	DB	46,0,13,4,12,-4,11,3,10,-5,9,0,129
;Instrumento 'Robo'
PAUTA_10:	DB	12,-1,12,-1,28,9,11,0,27,5,27,9,10,0,26,5,26,9,9,0,25,5,25,9,8,0,24,5,24,9,131
;Instrumento 'Chip'
PAUTA_11:	DB	70,0,7,0,40,0,7,0,6,0,5,0,129
;Instrumento 'Clipclop'
PAUTA_12:	DB	12,0,11,0,10,0,9,0,9,0,9,0,9,0,9,0,8,0,8,0,8,0,8,0,8,0,138
;Instrumento 'Eco'
PAUTA_13:	DB	9,0,8,0,7,0,6,0,129
;Instrumento 'Harmonica'
PAUTA_14:	DB	42,0,11,0,12,0,11,0,10,0,9,0,129
;Instrumento 'Onda'
PAUTA_15:	DB	73,0,10,0,11,0,12,0,11,0,10,0,9,0,6,0,129
;Instrumento 'Teeth'
PAUTA_16:	DB	73,0,10,0,42,0,9,0,8,0,7,0,7,0,7,0,7,0,6,0,6,0,6,0,6,0,136

;Efectos
;Efecto 'Bass Drum'
SONIDO0:	DB	209,60,0,15,124,0,255
;Efecto 'Bass Drum Vol 2'
SONIDO1:	DB	186,58,0,0,102,0,162,131,0,255
;Efecto 'Drum'
SONIDO2:	DB	231,46,0,115,43,1,100,42,2,255
;Efecto 'Drum 2'
SONIDO3:	DB	19,63,0,0,13,1,0,10,1,0,8,1,255
;Efecto 'Hit hat'
SONIDO4:	DB	0,12,1,0,6,1,255
;Efecto 'Hit Hat 2'
SONIDO5:	DB	0,12,1,255
;Efecto 'Bongo 1'
SONIDO6:	DB	186,30,0,232,25,0,0,40,0,69,38,0,255
;Efecto 'Bongo 2'
SONIDO7:	DB	69,46,0,186,41,0,46,56,0,232,54,0,255
;Efecto 'Drum 3'
SONIDO8:	DB	232,44,0,0,92,5,23,108,5,232,124,5,255
;Efecto 'Mute'
SONIDO9:	DB	0,0,0,255

;Frecuencias para las notas
DATOS_NOTAS: DW 0,0
DW 964,910,859,811,766,722,682,644,608,573
DW 541,511,482,455,430,405,383,361,341,322
DW 304,287,271,255,241,228,215,203,191,180
DW 170,161,152,143,135,128,121,114,107,101
DW 96,90,85,81,76,72,68,64,60,57
DW 54,51,48,45,43,40,38,36,34,32
