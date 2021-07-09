project "Glad"
    kind "StaticLib"
    language "C"
    staticruntime "on"
    
    targetdir (outputdirTarget .. "/%{prj.name}")
   	objdir (outputdirObject .. "/%{prj.name}")

    files
    {
        "include/**.h",
        "src/**.c"
    }
    
    filter "system:windows"
        systemversion "latest"

        includedirs
        {
            "include"
        }

    filter "system:macosx"
        systemversion "latest"
        toolset "clang"

        sysincludedirs 
        {
            "include"
        }

    filter "system:linux"
        systemversion "latest"
        toolset "clang"

        sysincludedirs 
        {
            "include"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        runtime "Release"
        optimize "on"