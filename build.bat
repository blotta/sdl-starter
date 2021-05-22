@echo off


@REM echo ONE: "%1"
@REM echo TWO: "%2"

:: Debug
set d_comp_flags=-g -std=c11 -Wall -Werror
set d_build_dir=build\debug

:: Release Config
set r_comp_flags=-std=c11 -Wall -Werror -O3
set r_build_dir=build\release


:: Default
set target=debug
set cc=gcc
set comp_flags=%d_comp_flags%
set src=src/*.c src/game_utils/*.c
set link=-lm -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
set build_dir=%d_build_dir%
set include=-Ivendor/include
set lib=-Lvendor/lib

if not "%1" == "release" (goto afterTarget)
    set target=release
    set comp_flags=%r_comp_flags%
    set build_dir=%r_build_dir%


:afterTarget
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
Xcopy /E /D /Y .\res\ .\%build_dir%\res\
