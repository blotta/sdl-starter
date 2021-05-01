# SDL Starter

Files:
* Source files in the `src` folder
* Vendor files in `vendor/bin`, `vendor/include` and `vendor/lib`
* Resource files in the `res` folder

Running `build.bat` will:
1. Compile files in the `src` folder into the `game.exe` executable (with debugging flags)
2. Copy all files in the `vendor/bin` folder contents to the `build` folder, if newer
3. Copy resources folder `res` to the `build` folder, if newer