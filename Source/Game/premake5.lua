include "../../Premake/extensions.lua"

workspace "Game"
	location "../../"
	startproject "Game"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Retail"
	}

-- include for common stuff 
include "../../Premake/common.lua"

include (dirs.external)
include (dirs.engine)


-------------------------------------------------------------
project "Game"
	location (dirs.projectfiles)
	dependson { "External", "Engine" }
		
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	debugdir "%{dirs.bin}"
	targetdir ("%{dirs.bin}")
	targetname("%{prj.name}_%{cfg.buildcfg}")
	objdir ("%{dirs.temp}/%{prj.name}/%{cfg.buildcfg}")

	links {"External", "Engine"}

	includedirs { dirs.external, dirs.engine, dirs.external.."/CommonUtilities/includes"  }

	files {
		"source/**.h",
		"source/**.cpp",
	}

	libdirs { dirs.lib, dirs.dependencies}

	verify_or_create_settings("Game")
	
	filter "configurations:Debug"
		defines {"_DEBUG"}
		runtime "Debug"
		symbols "on"
		files {"tools/**"}
		includedirs {"tools/"}
		libdirs{dirs.external.."/CommonUtilities/Debug/lib"}
		links{"CommonUtilities-Debug.lib"}
	filter "configurations:Release"
		defines "_RELEASE"
		runtime "Release"
		optimize "on"
		files {"tools/**"}
		includedirs {"tools/"}
		libdirs{dirs.external.."/CommonUtilities/Release/lib"}
		links{"CommonUtilities-Release.lib"}
	filter "configurations:Retail"
		defines "_RETAIL"
		runtime "Release"
		optimize "on"
		libdirs{dirs.external.."/CommonUtilities/Release/lib"}
		links{"CommonUtilities-Release.lib"}
		
	filter "system:windows"
--		kind "StaticLib"
		staticruntime "off"
		symbols "On"		
		systemversion "latest"
		warnings "Extra"
		--conformanceMode "On"
		--buildoptions { "/permissive" }
		flags { 
		--	"FatalWarnings", -- would be both compile and lib, the original didn't set lib
			"FatalCompileWarnings",
			"MultiProcessorCompile"
		}
		
		defines {
			"WIN32",
			"_LIB", 
			"TGE_SYSTEM_WINDOWS" 
		}