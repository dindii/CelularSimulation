#pragma once

#include "Defines.h"
#include <Math/vec2.h>
namespace CS
{
	class Framebuffer
	{
	public:
		Framebuffer(vec2<int32_t> dims);
		virtual ~Framebuffer();
	
		void Remake(vec2<int32_t> dims);
	
		void Bind();
		void UnBind();
	
		inline Handle GetRendererID() const { return m_RendererID; }
		inline Handle GetColorOutput() const { return m_ColorAttachment; }
	
	private:
		Handle m_RendererID;
		Handle m_ColorAttachment;
	};
}