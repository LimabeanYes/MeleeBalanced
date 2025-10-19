SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "shiek.c" -s ftFunction -dat "%FILESYS%PlSk.dat" -ow 

pause