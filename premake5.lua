workspace "Phys75"
    architecture "x64"
    startproject "Phys75-Example"

    configurations
    {
        "Debug",
        "Release"
    }

    outputdirTarget = "bin/%{cfg.buildcfg}/%{cfg.system}"
    outputdirObject = "bin-int/%{cfg.buildcfg}/%{cfg.system}"

    include "ThirdParty/glad"
    include "ThirdParty/glfw-3.3.4"

project "Phys75"
    location "%{prj.name}"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir (outputdirTarget .. "/%{prj.name}")
    objdir (outputdirObject .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"

        includedirs
        {
            "%{prj.name}/src",
			"ThirdParty/glm"
        }

        defines
        {
            "NOMINMAX"
        }

    filter "system:macosx"
        systemversion "latest"
        toolset "clang"

        sysincludedirs
        {
            "%{prj.name}/src",
			"ThirdParty/glm"
        }

    filter "system:linux"
        systemversion "latest"
        toolset "clang"

        sysincludedirs
        {
            "%{prj.name}/src",
			"ThirdParty/glm"
        }

    filter "configurations:Debug"
        defines "PHYS75_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "PHYS75_RELEASE"
        runtime "Release"
        symbols "on"

project "Phys75-Examples"
    location "%{prj.name}"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "off"

    targetdir (outputdirTarget .. "/%{prj.name}")
    objdir (outputdirObject .. "/%{prj.name}")

    files
    {
        "%{prj.name}/src/**.h",
        "%{prj.name}/src/**.cpp"
    }

    links
    {
        "Phys75"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    filter "system:windows"
        systemversion "latest"

        includedirs
        {
            "%{prj.name}/src",
			"Phys75/src",
			"ThirdParty/glm",
            "ThirdParty/glfw-3.3.4/include",
            "ThirdParty/glad/include"
        }

        defines
        {
            "NOMINMAX"
        }

    filter "system:macosx"
        systemversion "latest"
        toolset "clang"

        sysincludedirs
        {
            "%{prj.name}/src",
			"Phys75/src",
			"ThirdParty/glm",
            "ThirdParty/glfw-3.3.4/include",
            "ThirdParty/glad/include"
        }

    filter "system:linux"
        systemversion "latest"
        toolset "clang"

        sysincludedirs
        {
            "%{prj.name}/src",
			"Phys75/src",
			"ThirdParty/glm",
            "ThirdParty/glfw-3.3.4/include",
            "ThirdParty/glad/include"
        }

    filter "configurations:Debug"
        defines "PHYS75_DEBUG"
        runtime "Debug"
        symbols "on"

    filter "configurations:Release"
        defines "PHYS75_RELEASE"
        runtime "Release"
        symbols "on"
