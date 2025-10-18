SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "src/luigi.c" -s ftFunction -dat "%FILESYS%PlLg.dat" -ow 

pause