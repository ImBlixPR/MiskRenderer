workspace "3dGameEngine"
	
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
	}



project "3dGameEngine"
	
	location "3dGameEngine"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/%{cfg.buildcfg}/%{cfg.architecture}")
	objdir ("bin-int/%{cfg.buildcfg}/%{cfg.architecture}")

	files
	{
		"%{prj.name}/**.h",
		"%{prj.name}/**.cpp",
		"%{prj.name}/**.dll"
		

	}

	includedirs
	{
		"%{wks.location}/vendor/GLEW/include",
		"%{wks.location}/vendor/GLFW64/include",
		"%{wks.location}/vendor/GLM",
		"%{wks.location}/vendor/SDL/include",
		"%{wks.location}/vendor/SDL_Image/include"

	}

	libdirs
	{
		"%{wks.location}/vendor/GLEW/lib/Release/x64",
		"%{wks.location}/vendor/GLFW64/lib-vc2022",
		"%{wks.location}/vendor/SDL/lib/x64",
		"%{wks.location}/vendor/SDL_Image/lib/x64"
		
	}

			-- Link against OpenGL and external libraries
	links
	{
		"opengl32.lib",   -- OpenGL library
		"glew32.lib",     -- GLEW library
		"glfw3.lib", -- GLFW library
		"SDL2.lib",
		"SDL2main.lib",
		"SDL2_image.lib"
	}



    filter "system:windows"
        cppdialect "C++17"
        staticruntime "Off"  -- Set to "On" for static runtime or "Off" for dynamic runtime
        systemversion "latest"




	filter "configurations:Debug"
		defines "MK_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "MK_RELEASE"
		optimize "On"


