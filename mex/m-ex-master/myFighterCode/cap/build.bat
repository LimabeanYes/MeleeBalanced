SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "src/cap.c" -s ftFunction -dat "%FILESYS%PlCa.dat" -ow 

pause