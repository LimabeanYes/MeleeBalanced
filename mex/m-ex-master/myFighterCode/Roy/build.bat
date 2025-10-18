SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "roy.c" -s ftFunction -dat "%FILESYS%PlFe.dat" -ow 

pause
