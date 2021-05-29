@echo off

::::::::: CONFIG :::::::::

:: Example project
:: set project_src_dir=src/examples/follower
set project_src_dir=src/examples/snake


:: Resources folder (use Windows path divisor '\')
set res_dir=res


:: Target build (debug, release)
set target=debug

::::::: END CONFIG :::::::

:: Debug
set d_comp_flags=-g -std=c11 -Wall -Wno-unused-variable -DDEBUG
set d_build_dir=build\debug

:: Release Config
set r_comp_flags=-std=c11 -Wall -Werror -O3 -DNDEBUG
set r_build_dir=build\release


:: Default to debug
set cc=gcc
set comp_flags=%d_comp_flags%
set src=%project_src_dir%/*.c src/utils/*.c src/game_utils/*.c src/sdl_utils/*.c
set link=-lm -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
set build_dir=%d_build_dir%
set include=-Ivendor/include -Isrc/utils -Isrc/game_utils -Isrc/sdl_utils
set lib=-Lvendor/lib

if "%target%" == "release" (call :SetTargetToRelease)
if "%1" == "release" (call :SetTargetToRelease)
if "%1" == "debug" (call :SetTargetToDebug)

set executable_path=%build_dir%\game.exe
set compile_cmd=%cc% %comp_flags% %src% -o %executable_path% %include% %lib% %link%


:: Summary
@REM echo TARGET: %target%
@REM echo CMD: %compile_cmd%

:: Do stuff
if not exist .\%build_dir% mkdir .\%build_dir%

:: Compile
@echo on
%compile_cmd%
@echo off

:: Copying runtime dlls
echo Copying runtime
@REM Xcopy /E /D /Y /L .\vendor\bin\* .\build\*
Xcopy /E /D /Y .\vendor\bin\* .\%build_dir%\*

echo Copying resources
:: Copying asset directory (res) recursively (/E) if newer (/D) noconfirm (/Y)
@REM Xcopy /E /D /Y /L .\res\ .\build\res\
Xcopy /E /D /Y .\%res_dir%\ .\%build_dir%\%res_dir%\


EXIT /B %ERRORLEVEL%

echo should not run this line

:: Functions
:SetTargetToRelease
    set target=release
    set comp_flags=%r_comp_flags%
    set build_dir=%r_build_dir%
EXIT /B 0

:SetTargetToDebug
    set target=debug
    set comp_flags=%d_comp_flags%
    set build_dir=%d_build_dir%
EXIT /B 0
