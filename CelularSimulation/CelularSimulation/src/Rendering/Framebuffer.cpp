#include "Framebuffer.h"

#include <Core/Application.h>
#include <glad/glad.h>

//#TOREMOVE
#include <iostream>

namespace CS
{
	Framebuffer::Framebuffer(vec2<int32_t> dims)
	{
		Remake(dims);
	}

	Framebuffer::~Framebuffer()
	{
	}

	void Framebuffer::Remake(vec2<int32_t> dims)
	{
		if (m_RendererID)
		{
			glDeleteFramebuffers(1, &m_RendererID);
			glDeleteTextures(1, &m_ColorAttachment);


			m_RendererID = 0;
			m_ColorAttachment = 0;
		}

		glCreateFramebuffers(1, &m_RendererID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);

		// -------------------- Color attachment
		glGenTextures(1, &m_ColorAttachment);
		glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);


		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, dims.x, dims.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
		// --------------------


		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Failed to create OpenGL Framebuffer!" << std::endl;

		UnBind();
	}

	void Framebuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
	}

	void Framebuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

}