# SDL Starter

## Files
* Source files in the `src/` folder
    - Example projects are separated in the `src/examples/{project}` directories
    - Helper modules separated into `src/{module}` directories
* Vendor files in `vendor/`
* Resource files in the `res/` folder

## Helper Modules
Helper generic functions for working with SDL and C. Separated into `src/{module}`
* `utils`: Generic C utilities that don't depend on vendor libraries or other modules
* `game_utils`: Common game development utilities that can depend on the `utils` module, but doesn't depend on SDL or other vendor libraries
* `sdl_utils`: Utilities to work with SDL. Depends on SDL and can depend on the `game_utils` and `utils` modules

## Dependencies

Place the following dependencies on the `vendor/` directory:

* SDL2-2.28.5


This project uses [Premake](https://premake.github.io/download) to generate the project files.

## Building with Premake5

Run `premake5.exe <action>`

> Tested actions: `vs2022`

