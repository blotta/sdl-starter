
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.arquitecture}"
sdl_location = "vendor/SDL2-2.28.5"

workspace "sdl-starter"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release",
        "Dist"
    }

    filter "configurations:Debug"
        defines "SDLST_DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "SDLST_RELEASE"
        optimize "On"

    filter "configurations:Dist"
        defines "SDLST_DIST"
        optimize "On"


project "sauce"
    location "src/%{prj.name}"
    kind "StaticLib"
    language "C"

    targetdir ("bin/" .. outputdir .. "%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "%{prj.name}")

    files
    {
        "src/%{prj.name}/**.h",
        "src/%{prj.name}/**.c",
    }

    filter "system:windows"
        cdialect "C11"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "SAUCE_PLATFORM_WINDOWS"
        }


project "sdl_sauce"
    location "src/%{prj.name}"
    kind "StaticLib"
    language "C"
    dependson "game_utils"

    targetdir ("bin/" .. outputdir .. "%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "%{prj.name}")

    files
    {
        "src/%{prj.name}/**.h",
        "src/%{prj.name}/**.c",
    }

    libdirs { sdl_location .. "/lib/x64" }

    includedirs { sdl_location .. "/include", "src/sauce/utils", "src/sauce/game_utils"}

    links { "sauce", "SDL2", "SDL2main" }

    defines { "SDL_SAUCE" }

    filter "system:windows"
        cdialect "C11"
        staticruntime "On"
        systemversion "latest"

        defines
        {
            "SDL_SAUCE_PLATFORM_WINDOWS"
        }

group "examples"

project 'snake'
    location "src/examples/%{prj.name}"
    kind "ConsoleApp"
    language "C"
    dependson "sdl_sauce"

    targetdir ("bin/" .. outputdir .. "%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "%{prj.name}")

    files
    {
        "src/examples/%{prj.name}/**.h",
        "src/examples/%{prj.name}/**.c",
    }

    libdirs { sdl_location .. "/lib/x64" }

    includedirs { sdl_location .. "/include", "src/sauce/utils", "src/sauce/game_utils", "src/sdl_sauce"}

    links { "sauce", "sdl_sauce", "SDL2", "SDL2main" }

    filter "system:windows"
        cdialect "C11"
        staticruntime "On"
        systemversion "latest"

    -- TODO: fix issue when copying runtime
    -- postbuildcommands
    -- {
    --     "{COPYFILE} " .. sdl_location .."/lib/x64/SDL2.dll %{cfg.buildtarget.directory}SDL2.dll"
    -- }

project 'follower'
    location "src/examples/%{prj.name}"
    kind "ConsoleApp"
    language "C"
    dependson "sdl_sauce"

    targetdir ("bin/" .. outputdir .. "%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "%{prj.name}")

    files
    {
        "src/examples/%{prj.name}/**.h",
        "src/examples/%{prj.name}/**.c",
    }

    libdirs { sdl_location .. "/lib/x64" }

    includedirs { sdl_location .. "/include", "src/sauce/utils", "src/sauce/game_utils", "src/sdl_sauce"}

    links { "sauce", "sdl_sauce", "SDL2", "SDL2main" }

    filter "system:windows"
        cdialect "C11"
        staticruntime "On"
        systemversion "latest"

    -- TODO: fix issue when copying runtime
    -- postbuildcommands
    -- {
    --     "{COPYFILE} " .. sdl_location .."/lib/x64/SDL2.dll %{cfg.buildtarget.directory}SDL2.dll"
    -- }

project 'wave_shooter'
    location "src/examples/%{prj.name}"
    kind "ConsoleApp"
    language "C"
    dependson "sdl_sauce"

    targetdir ("bin/" .. outputdir .. "%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "%{prj.name}")

    files
    {
        "src/examples/%{prj.name}/**.h",
        "src/examples/%{prj.name}/**.c",
    }

    libdirs { sdl_location .. "/lib/x64" }

    includedirs { sdl_location .. "/include", "src/sauce/utils", "src/sauce/game_utils", "src/sdl_sauce"}

    links { "sauce", "sdl_sauce", "SDL2", "SDL2main" }

    filter "system:windows"
        cdialect "C11"
        staticruntime "On"
        systemversion "latest"

    -- TODO: fix issue when copying runtime
    -- postbuildcommands
    -- {
    --     "{COPYFILE} " .. sdl_location .."/lib/x64/SDL2.dll %{cfg.buildtarget.directory}SDL2.dll"
    -- }

project 'sdl_gl'
    location "src/examples/%{prj.name}"
    kind "ConsoleApp"
    language "C"
    dependson "sdl_sauce"

    targetdir ("bin/" .. outputdir .. "%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "%{prj.name}")

    files
    {
        "src/examples/%{prj.name}/**.h",
        "src/examples/%{prj.name}/**.c",
    }

    libdirs { sdl_location .. "/lib/x64" }

    includedirs { sdl_location .. "/include", "src/sauce/utils", "src/sauce/game_utils", "src/sdl_sauce"}

    links { "sauce", "sdl_sauce", "SDL2", "SDL2main", "opengl32" }

    filter "system:windows"
        cdialect "C11"
        staticruntime "On"
        systemversion "latest"

    -- TODO: fix issue when copying runtime
    -- postbuildcommands
    -- {
    --     "{COPYFILE} " .. sdl_location .."/lib/x64/SDL2.dll %{cfg.buildtarget.directory}SDL2.dll"
    -- }
group ""
