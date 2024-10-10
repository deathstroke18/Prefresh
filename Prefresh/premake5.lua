workspace "Prefresh"
  configurations {"Debug", "Release"}
  -- Use C++ as the target language for all builds
  language "C++"
  targetdir "bin/%{cfg.buildcfg}"

  -- Get that C++14 goodness
  flags { "C++14" }

  filter "configurations:Debug"
    -- Add the preprocessor definition DEBUG to debug builds
    defines { "DEBUG" }
    -- Ensure symbols are bundled with debug builds
    flags { "Symbols" }

  filter "configurations:Release"
    -- Add the preprocessor definition RELEASE to debug builds
    defines { "RELEASE" }
    -- Turn on compiler optimizations for release builds
    optimize "On"

  -- Prefresh Library
  project "Prefresh"
    kind "SharedLib"
    -- recursively glob .h and .cpp files in the lib directory
    files { "lib/**.h", "lib/**.cpp" }

  -- Prefresh Runtime
  project "PrefreshRuntime"
    kind "ConsoleApp"
    -- recursively glob .h and .cpp files in the runtime directory
    files { "runtime/**.h", "runtime/**.cpp", "test/pub/*.h" }
    -- link the Prefresh library at runtime
    links { "Prefresh" }
    includedirs { "lib/pub", "test/pub" }
    -- Ensure it looks for the shared library in the correct directory
    libdirs { "bin/%{cfg.buildcfg}" }

  project "PrefreshTest"
    kind "SharedLib"
    files {"test/**.h", "test/**.cpp", "test/pub/*.h"}