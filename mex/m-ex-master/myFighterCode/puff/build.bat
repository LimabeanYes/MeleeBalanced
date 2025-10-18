SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "puff.c" -s ftFunction -dat "%FILESYS%PlPr.dat" -ow 

pause
