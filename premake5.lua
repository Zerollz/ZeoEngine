workspace "Zeo"
	architecture "x64"
	startproject "Sandbx"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory)
IncludeDir ={}
IncludeDir["GLFW"] = "Zeo/vendor/GLFW/include"
IncludeDir["Glad"] = "Zeo/vendor/Glad/include"
IncludeDir["ImGui"] = "Zeo/vendor/imgui"
IncludeDir["glm"] = "Zeo/vendor/glm"
IncludeDir["stb_image"] = "Zeo/vendor/stb_image"

include "Zeo/vendor/GLFW"
include "Zeo/vendor/Glad"
include "Zeo/vendor/imgui"

project "Zeo"
	location "Zeo"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "zopch.h"
	pchsource "Zeo/src/zopch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
		"Dwmapi.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ZO_PLATFORM_WINDOWS",
			"ZO_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
	
	filter "configurations:Debug"
		defines "ZO_DEBUG"
		runtime "Debug"
		symbols "on"


	filter "configurations:Release"
		defines "ZO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ZO_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Zeo/vendor/spdlog/include",
		"Zeo/src",
		"%{IncludeDir.glm}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"Zeo"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"ZO_PLATFORM_WINDOWS"
		}

	
	filter "configurations:Debug"
		defines "ZO_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "ZO_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "ZO_DIST"
		runtime "Release"
		optimize "on"
