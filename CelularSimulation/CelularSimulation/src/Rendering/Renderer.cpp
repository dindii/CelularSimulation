#include "Renderer.h"
#include "Defines.h"

#include <Core/Application.h>
#include "LowLevelMesh.h"

#include <glad/glad.h>


#include <vector>
#include <string>


namespace CS
{
	std::unique_ptr<Framebuffer> Renderer::GPUTexture;
	std::unique_ptr<LowLevelMesh> Renderer::GPUQuad;

	void Renderer::Init()
	{
		vec2<int32_t> dims = Application::GetInstance().GetWindow()->GetDims();
		
		//This will be the texture that we will upload our CPU pixel buffer to.
		GPUTexture = std::make_unique<Framebuffer>(dims);

		//This is for our plane that will contain the screen-texture of the application. Positions are in NDC. 
		//We will get the texture from the framebuffer (which contains our pixel-buffer) and render it here.
		std::vector<float> quadNDCVertices = { 
			-1.0f,  1.0f,
			-1.0f, -1.0f,
			 1.0f, -1.0f,
			-1.0f,  1.0f,
			 1.0f, -1.0f,
			 1.0f,  1.0f };

		std::vector<float> quadUVs = {
			 0.0f, 1.0f,
			 0.0f, 0.0f,
			 1.0f, 0.0f,
			 
			 0.0f, 1.0f,
			 1.0f, 0.0f,
			 1.0f, 1.0f
		};

		GPUQuad = std::make_unique<LowLevelMesh>(std::string("res/Shaders/ScreenVertex.glsl"), std::string("res/Shaders/ScreenFragment.glsl"), std::move(quadNDCVertices), std::move(quadUVs));
	}

	bool Renderer::Shutdown()
	{
		return false;
	}

	void Renderer::Draw()
	{
		GPUQuad->Bind();

		Clear();
		glDrawArrays(GL_TRIANGLES, 0, GPUQuad->GetVertexCount());
	}

	void Renderer::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer::SetClearColor(vec4<float>& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Renderer::SetViewport(vec2<int32_t> position, vec2<int32_t> size)
	{
		glViewport(position.x, position.y, size.x, size.y);
	}


}