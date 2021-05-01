:: Compile Debug
set build_dir=build\web
if not exist .\%build_dir% mkdir .\%build_dir%
emcc ^
src/main.c src/game_time.c src/move.c src/vec.c ^
-o %build_dir%/game.html ^
-Ivendor/include ^
-Lvendor/lib ^
-lm -lSDL2main -lSDL2 -lSDL2_image

:: -g -std=c11 -Wall ^
:: -lmingw32
:: Compile Release
:: set build_dir=build\release
:: if not exist .\%build_dir% mkdir .\%build_dir%
:: gcc ^
:: -std=c11 -Wall -O3 ^
:: src/*.c ^
:: -o %build_dir%/game.exe ^
:: -Ivendor/include ^
:: -Lvendor/lib ^
:: -lm -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

@echo off
@REM :: Copying runtime dlls
@REM echo Copying runtime
@REM @REM Xcopy /E /D /Y /L .\vendor\bin\* .\build\*
@REM Xcopy /E /D /Y .\vendor\bin\* .\%build_dir%\*

@REM echo Copying resources
@REM :: Copying asset directory (res) recursively (/E) if newer (/D) noconfirm (/Y)
@REM @REM Xcopy /E /D /Y /L .\res\ .\build\res\
@REM Xcopy /E /D /Y .\res\ .\%build_dir%\res\