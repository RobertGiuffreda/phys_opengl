workspace "BallPhys"
	architecture "x86"
	startproject "BallPhys"

	configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "./depend/glad/premake5.lua"
include "./depend/GLFW/premake5.lua"
include "./depend/stb_image/premake5.lua"

project "BallPhys"
	location "BallPhys"
	kind "ConsoleApp"
	language "C++"
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{wks.location}/depend/GLFW/include",
		"%{wks.location}/depend/glad/include",
		"%{wks.location}/depend/glm",
		"%{wks.location}/depend/stb_image"
	}

	links
	{
		"GLFW",
		"Glad",
		"stb_image",
		"opengl32.lib"
	}