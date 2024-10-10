workspace "Prefresh"
    configurations { "Debug", "Release" }
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"

    -- Use C++14 for the project
    cppdialect "C++14"

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"  -- Enable debug symbols

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "On"  -- Enable optimizations

    -- Prefresh Library
    project "Prefresh"
        kind "SharedLib"
        files { "lib/**.h", "lib/**.cpp" }

    -- Prefresh Runtime
    project "PrefreshRuntime"
        kind "ConsoleApp"
        files { "runtime/**.h", "runtime/**.cpp", "test/pub/*.h" }
        links { "Prefresh", "GoogleTest" }
        includedirs { "lib/pub", "test/pub", "googletest/googletest/include" }
        libdirs { "bin/%{cfg.buildcfg}" }

    -- Prefresh Test
    project "PrefreshTest"
        kind "SharedLib"
        files { "test/**.h", "test/**.cpp", "test/pub/*.h" }

    -- GoogleTest Project
    project "GoogleTest"
        kind "StaticLib"
        files { "googletest/googletest/src/gtest-all.cc" }
        includedirs { "googletest/googletest/include", "googletest/googletest" }
