@echo off

if "%1" == "upload" goto :upload
if "%1" == "run" goto :run
if "%1" == "clean" goto :clean

REM Default target
if "%1" == "" goto :upload

echo Invalid target: %1
echo Usage: .\make.bat [upload^|run^|clean]
goto :eof

:upload
	pio run -t upload -e uno
	goto :eof

:run
	pio run -t upload -t monitor -e uno
	goto :eof

:clean
	rd /s /q .pio
	goto :eof
