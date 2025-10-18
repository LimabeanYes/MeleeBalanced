SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "src/gnw.c" -s ftFunction -dat "%FILESYS%PlGw.dat" -ow 

pause