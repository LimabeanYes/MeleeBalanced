SET "TKPATH=../../MexTK/"
SET "FILESYS=../../../../files/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "src/toad.c" -s ftFunction -dat "%FILESYS%PlTd.dat" -ow 

:: compile item code
"%TKPATH%MexTK.exe" -ff -item 0 "src/item_fireball.c" -dat "%FILESYS%PlTd.dat" -s itFunction -ow

pause
