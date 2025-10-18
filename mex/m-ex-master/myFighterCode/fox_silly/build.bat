SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "fox.c" -s ftFunction -dat "%FILESYS%PlFx.dat" -ow 

pause