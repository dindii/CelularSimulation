#include "Renderer.h"
#include "Defines.h"

#include <Core/Application.h>
#include "LowLevelMesh.h"

#include <glad/glad.h>


#include <vector>
#include <string>

#include <chrono>

namespace CS
{
	std::unique_ptr<GPUTexture2D> Renderer::GPUTexture;
	std::unique_ptr<CPUTexture2D> Renderer::CPUTexture;

	std::unique_ptr<LowLevelMesh> Renderer::GPUQuad;
	
	vec4<float> Renderer::m_ClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	void Renderer::Init()
	{
		vec2<int32_t> dims = Application::GetInstance().GetWindow()->GetDims();
		SetViewport({ 0, 0 }, { dims.x, dims.y });
		
		//This will be our CPU pixel buffer that we will write to.
		CPUTexture = std::make_unique<CPUTexture2D>(dims.x, dims.y, 4);
		
		//This will be the texture that we will upload our CPU pixel buffer to.
		GPUTexture = std::make_unique<GPUTexture2D>(nullptr, dims.x, dims.y, 4);
		


		//This is for our plane that will contain the screen-texture of the application. Positions are in NDC. 
		//We will get the texture from the framebuffer (which contains our pixel-buffer) and render it here.
		std::vector<float> quadNDCVertices = { 
			-1.0f,  1.0f,  0.0f,
			-1.0f, -1.0f,  0.0f,
			 1.0f, -1.0f,  0.0f,
			-1.0f,  1.0f,  0.0f,
			 1.0f, -1.0f,  0.0f,
			 1.0f,  1.0f,  0.0f
		};



		std::vector<float> quadUVs = {
			 0.0f, 0.0f,  
			 0.0f, 1.0f,  
			 1.0f, 1.0f,  
			 			  
			 0.0f, 0.0f,  
			 1.0f, 1.0f,  
			 1.0f, 0.0f
		};


		GPUQuad = std::make_unique<LowLevelMesh>(std::string("res/Shaders/ScreenVertex.glsl"), std::string("res/Shaders/ScreenFragment.glsl"), std::move(quadNDCVertices), std::move(quadUVs));

		SetClearColor(vec4<float>( 0.5f, 0.5f, 0.5f, 1.0f));
	}

	bool Renderer::Shutdown()
	{
		return false;
	}

	void Renderer::Draw()
	{
		GPUQuad->Bind();
		GPUQuad->GetShader()->SetUint("screenTexture", 1);
		GPUTexture->Bind(1);

		std::vector<uint8_t>& pixels = CPUTexture->GetPixels();
		GPUTexture->SetData(pixels.data());

		Clear();

		glDrawArrays(GL_TRIANGLES, 0, GPUQuad->GetVertexCount());
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::SetClearColor(vec4<float>& color)
	{
		m_ClearColor = color;
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::SetViewport(vec2<int32_t> position, vec2<int32_t> size)
	{
		glViewport(position.x, position.y, size.x, size.y);
	}
	void Renderer::SetPixel(vec2<uint32_t> coord, vec4<uint8_t> color)
	{
		CPUTexture->SetPixel(coord.x, coord.y, color);
	}
}