#pragma once

#include "GPUTexture2D.h"
#include "CPUTexture2D.h"

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
		static const vec4<float>& GetClearColor() { return m_ClearColor; }

		static void SetViewport(vec2<int32_t> position, vec2<int32_t> size);

		static void SetPixel(vec2<uint32_t> coord, vec4<uint8_t> color);

	private:
		static std::unique_ptr<GPUTexture2D> GPUTexture;
		static std::unique_ptr<CPUTexture2D> CPUTexture;

		//This is the quad that will occupy the screen, this is where we will render our screen texture (previously rendered offscreen) to.
		static std::unique_ptr<LowLevelMesh> GPUQuad;

		static vec4<float> m_ClearColor;
	};
}