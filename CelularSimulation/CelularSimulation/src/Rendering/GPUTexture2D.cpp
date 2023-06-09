#include "GPUTexture2D.h"

#include <glad/glad.h>

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stbi/stb_image.h>

namespace CS
{
	GPUTexture2D::GPUTexture2D() : m_Width(0), m_Height(0), m_InternalFormat(0), m_DataFormat(0), m_RendererID(0)
	{

	}

	
	void GPUTexture2D::LoadTextureFromData(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels)
	{
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;

		stbi_set_flip_vertically_on_load(true);

		switch (channels)
		{
		case 1:
		{
			internalFormat = GL_R8;
			dataFormat = GL_RED;
			break;
		}
		case 3:
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
			break;
		}
		case 4:
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
			break;
		}
		default:
		{
			std::cout << "Unknown texture format type!";
			return;
		}
		}

		glGenTextures(1, &m_RendererID);
		glBindTexture(GL_TEXTURE_2D, m_RendererID);

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_RendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);


		//This will give the user the freedom to start a blank texture so he can fill it later on.
		//The only requisite is to pre-config the texture with width, height and channels to make sure it's valid
		//If stbi could not load the image, we will catch this error in the switch above since we won't have any channel set.
		if (data)
		{
			glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
			glBindTexture(GL_TEXTURE_2D, 0);
			return;
		}

		std::cout << "Texture's data is not set!";
	}

	GPUTexture2D::GPUTexture2D(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels /*= 4*/)
	{
		LoadTextureFromData(data, width, height, channels);
	}

	GPUTexture2D::GPUTexture2D(const std::string& path) : m_Path(path)
	{
		int width = 0, height = 0, channels = 0;

		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

		if (!data)
		{
			std::cout << "Could not load texture, please check the path!";
			return;
		}

		LoadTextureFromData(data, width, height, channels);
		stbi_image_free(data);
	}

	GPUTexture2D::~GPUTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void GPUTexture2D::SetData(void* data)
	{
		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
	}

	void GPUTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}
}