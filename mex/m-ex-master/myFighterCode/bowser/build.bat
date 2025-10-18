SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "src/bowser.c" -s ftFunction -dat "%FILESYS%PlKp.dat" -ow 

pause