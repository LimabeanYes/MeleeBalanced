SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "rng.c" -s grFunction -dat "%FILESYS%GrRng.dat" -ow 

pause