SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "grgr.c" -s grFunction -dat "%FILESYS%GrGr2.dat" -ow 

pause