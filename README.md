# SDL Starter

## Files
* Source files in the `src` folder
    - Example projects are separated in the `src/examples/{project}` directories
    - Helper modules separated into `src/{module}` directories
* Vendor files in `vendor/bin`, `vendor/include` and `vendor/lib`
* Resource files in the `res` folder

## Helper Modules
Helper generic functions for working with SDL and C. Separated into `src/{module}`
* `utils`: Generic C utilities that don't depend on vendor libraries or other modules
* `game_utils`: Common game development utilities that can depend on the `utils` module, but doesn't depend on SDL or other vendor libraries
* `sdl_utils`: Utilities to work with SDL. Depends on SDL and can depend on the `game_utils` and `utils` modules

## Building

Running `build.bat`:
1. Configure file:
    - `project_src_dir`: project directory
    - `res_dir`: resources directory
    - `target`: `debug` or `release`
2. Compiles files in the `src` folder into a `game.exe` executable
    - Debug by default. Run `build.bat release` for optimized build
    - Output directory: `build/{target}/`
3. Copies all files in the `vendor/bin` folder contents to the appropriate build folder, if newer
4. Copies resources folder `res` to the appropriate build folder, if newer