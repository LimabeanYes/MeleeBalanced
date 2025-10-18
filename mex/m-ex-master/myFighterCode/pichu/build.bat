SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "src/pichu.c" -s ftFunction -dat "%FILESYS%PlPc.dat" -ow 

pause
