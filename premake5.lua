workspace "threadstone"
    configurations { 
        "Debug",
        "Release"
    }

project "threadstone"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    files { "*.cpp" }

    includedirs { "include" }

    libdirs { "libs" }
    links { "glew32s", "SDL3", "opengl32" }

    defines { "GLEW_STATIC" }
    
    filter "configurations:Debug"
        defines {
            "DEBUG"
        }
        symbols "On"

    filter "configurations:Release"
        defines {
            "NDEBUG"
        }
        optimize "On"