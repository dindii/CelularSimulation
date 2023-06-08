#pragma once

#include "Framebuffer.h"
#include "LowLevelMesh.h"

#include <Math/vec2.h>
#include <Math/vec4.h>

#include <memory>

namespace CS
{
	class Renderer
	{
	public:
		Renderer() = delete;

		static void Init();
		static bool Shutdown();
		
		static void Draw();
		static void Clear();

		static void SetClearColor(vec4<float>& color);
		static void SetViewport(vec2<int32_t> position, vec2<int32_t> size);

	private:
		static std::unique_ptr<Framebuffer> GPUTexture;

		//This is the quad that will occupy the screen, this is where we will render our screen texture (previously rendered offscreen) to.
		static std::unique_ptr<LowLevelMesh> GPUQuad;
	};
}