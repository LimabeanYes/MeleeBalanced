SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "cup.c" -s grFunction -dat "%FILESYS%GrCup.dat" -ow 

pause