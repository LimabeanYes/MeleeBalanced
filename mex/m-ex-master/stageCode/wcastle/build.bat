SET "TKPATH=../../Tools/MexTK/"
SET "FSPATH=../../stage_src/warios_castle/"

:: compile main code
"%TKPATH%MexTK.exe" -ff -i "WariosCastle.c" -s grFunction -t "%TKPATH%grfunction.txt" -l "%TKPATH%melee.link" -dat "%FSPATH%GrWarioCastle.dat" -ow

pause