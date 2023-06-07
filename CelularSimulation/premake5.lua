workspace "CelularSimulation"
		architecture "x64"
		startproject "SandBox"


configurations
{
	"Debug",
	"Release",
	"Dist"
}

characterset ("MBCS")

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

 IncludeDir = {}
  IncludeDir["Glad"] = "CelularSimulation/vendor/Glad/include"
  IncludeDir["stbi"] = "CelularSimulation/vendor/stbi"

  group "Dependencies"
  include "CelularSimulation/vendor/Glad"
  group ""

project "CelularSimulation"
	location "CelularSimulation"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	toolset "v143"  

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")


	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.stbi}"
	}
	
	links
	{
		"Glad"
	}

	filter "system:windows"
	systemversion "10.0.22621.0"

	defines
	{
		"CS_PLATFORM_WINDOWS"
	}

	filter "configurations:Debug"
	defines "CS_DEBUG"
	runtime "Debug"
	symbols "on"

	filter "configurations:Release"
	defines "CS_DEBUG"
	runtime "Release"
	optimize "Debug"

	filter "configurations:Dist"
	defines "CS_DIST"
	runtime "Release"
	symbols "Off"
	optimize "Full"