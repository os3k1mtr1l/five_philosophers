workspace "2D_Template"
    filename "main"
    configurations { "Debug", "Release" }
    platforms { "Win64" }

project "ImGui"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    includedirs {
        "third_party/libs/includes/imgui",
        "third_party/libs/includes/rlimgui",
		"third_party/libs/includes/raylib"
    }

    files {
        "third_party/libs/includes/imgui/*.cpp",
        "third_party/libs/includes/imgui/*.h",
		"third_party/libs/includes/rlimgui/*.cpp",
        "third_party/libs/includes/rlimgui/*.h"
    }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

project "2D_Template"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    architecture "x86_64"
    
    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    files { "src/header/*.h", "src/*.cpp" }
    links { "raylib", "gdi32", "winmm", "opengl32", "ImGui" }
    includedirs { "third_party/libs/includes/*" }

    filter "action:gmake"
        libdirs { "third_party/libs/binaries/mingw" }
        postbuildcommands {
            "{COPY} third_party/libs/binaries/mingw/raylib.dll bin/%{cfg.buildcfg}"
        }

    filter "action:vs*"
        libdirs { "third_party/libs/binaries/msvc" }
        postbuildcommands {
            "{COPY} third_party/libs/binaries/msvc/raylib.dll bin/%{cfg.buildcfg}"
        }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"