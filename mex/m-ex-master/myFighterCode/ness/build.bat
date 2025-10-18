SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "src/ness.c" -s ftFunction -dat "%FILESYS%PlNs.dat" -ow 

pause