@echo off
rem Do not edit! This batch file is created by CASIO fx-9860G SDK.


if exist HEXAGON.G1A  del HEXAGON.G1A

cd debug
if exist FXADDINror.bin  del FXADDINror.bin
"C:\CASIO\fx-9860G SDK\OS\SH\Bin\Hmake.exe" Addin.mak
cd ..
if not exist debug\FXADDINror.bin  goto error

"C:\CASIO\fx-9860G SDK\Tools\MakeAddinHeader363.exe" "C:\users\eiyeron\My Documents\Programming\SDK\fxsdk\Super-Hexagon-Casio"
if not exist HEXAGON.G1A  goto error
echo Build has completed.
goto end

:error
echo Build was not successful.

:end

