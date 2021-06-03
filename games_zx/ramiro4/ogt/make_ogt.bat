@echo off

set base=0xF000
set basesfx=0xFD00

if [%1]==[justassemble] goto :assemble

echo Convirtiendo . . .
..\utils\AKSToBIN.exe -a %base% title.aks 00_title.bin 
..\utils\AKSToBIN.exe -a %base% ingame.aks 01_ingame.bin 
..\utils\AKSToBIN.exe -a %base% hurry.aks 02_hurry.bin 
..\utils\AKSToBIN.exe -a %base% gover.aks 03_gover.bin 
..\utils\AKSToBIN.exe -a %base% ending.aks 04_ending.bin 
..\utils\AKSToBIN.exe -a %base% blank.aks 05_blank.bin 
..\utils\AKSToBIN.exe -s -a %basesfx% sfx.aks sfx.bin

echo Comprimiendo . . .
..\utils\apack.exe 00_title.bin 00_title_c.bin > nul
..\utils\apack.exe 01_ingame.bin 01_ingame_c.bin > nul
..\utils\apack.exe 02_hurry.bin 02_hurry_c.bin > nul
..\utils\apack.exe 03_gover.bin 03_gover_c.bin > nul
..\utils\apack.exe 04_ending.bin 04_ending_c.bin > nul
..\utils\apack.exe 05_blank.bin 05_blank_c.bin > nul
..\utils\apack.exe sfx.bin sfx_c.bin > nul

:assemble
echo Ensamblando . . .
..\utils\pasmo.exe atPlayer.speccy.asm RAM1.bin RAM1.map.txt
