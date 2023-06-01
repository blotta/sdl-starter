@echo off

::::::::: CONFIG :::::::::

:: Example project
set project_src_dir=src/examples/wave_shooter
@REM set project_src_dir=src/examples/snake


:: Resources folder (use Windows path divisor '\')
set res_dir=res


:: Target build (debug, release)
set target=debug

::::::: END CONFIG :::::::

:: Debug
set d_comp_flags=-g -std=c11 -Wall -Wno-unused-variable -DDEBUG
set d_build_dir=build\debug

:: Release Config
set r_comp_flags=-std=c11 -Wall -Werror -O2 -DNDEBUG
set r_build_dir=build\release


:: Default to debug
set cc=gcc
set comp_flags=%d_comp_flags%

set "utils_srcs="
for /r "src\utils" %%i in (*.c) do call set "utils_srcs=%%utils_srcs%% "%%i""

set "gameutils_srcs="
for /r "src\game_utils" %%i in (*.c) do call set "gameutils_srcs=%%gameutils_srcs%% "%%i""

set "sdlutils_srcs="
for /r "src\sdl_utils" %%i in (*.c) do call set "sdlutils_srcs=%%sdlutils_srcs%% "%%i""

set "project_srcs="
for /r "%project_src_dir%" %%i in (*.c) do call set "project_srcs=%%project_srcs%% "%%i""

set src=%utils_srcs% %gameutils_srcs% %sdlutils_srcs% %project_srcs% 

set link=-lm -lmingw32 -lSDL2main -lSDL2_image -lSDL2
set build_dir=%d_build_dir%
set include=-Ivendor/include -Isrc/utils -Isrc/game_utils -Isrc/sdl_utils
set lib=-Lvendor/lib


if "%target%" == "release" (call :SetTargetToRelease)
if "%1" == "release" (call :SetTargetToRelease)
if "%1" == "debug" (call :SetTargetToDebug)

set executable_path=%build_dir%\game.exe

@REM emscripten changes (uncomment to use)
rem set cc=emcc -D_GNU_SOURCE -sUSE_SDL=2 -sUSE_SDL_IMAGE=2
rem set link=-lm -lSDL2_image -lSDL2
rem set lib=
rem set executable_path=%build_dir%\index.html


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
