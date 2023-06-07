project "Glad"
    kind "StaticLib"
    language "C"
	staticruntime "on"
    toolset "v143"

    targetdir ("bin/" .. outputdir .. "/%{prj.name}")
    objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

    files
    {
        "include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
    }

	includedirs
	{
		"include"
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