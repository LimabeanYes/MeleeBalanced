SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "peach.c" -s ftFunction -dat "%FILESYS%PlPe.dat" -ow 

pause