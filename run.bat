@echo off
setlocal

set PARAMS=%*

echo Compiling ezc

:: gcc src/main.c -o ezc.exe

if not  exist build mkdir build

cd build
cmake -G "Unix Makefiles" ..
::cmake -G "Visual Studio 17 2022" ..
make
cd ..

if %errorlevel% neq 0 (
	echo Compilation failed
	exit /b %errorlevel%
)

echo Running ezc.exe
.\build\ezc.exe

endlocal