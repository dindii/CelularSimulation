#pragma once

#include "Defines.h"
#include <string_view>

namespace CS
{
	class GPUTexture2D
	{
	public:
		GPUTexture2D(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels = 4);
		GPUTexture2D(const std::string& path);
		GPUTexture2D();

		virtual ~GPUTexture2D();

		virtual uint32_t GetWidth()   const { return m_Width; }
		virtual uint32_t GetHeight()  const { return m_Height; }
		virtual uint32_t GetID()      const { return m_RendererID; }
		virtual std::string_view GetPath()const { return m_Path; }
		
		virtual void SetData(void* data);

		virtual void Bind(uint32_t slot = 0) const;

	private:
		void LoadTextureFromData(const uint8_t* data, const uint32_t width, const uint32_t height, const uint32_t channels);

	private:
		uint32_t m_Width, m_Height;
		uint32_t m_InternalFormat, m_DataFormat;
		
		std::string m_Path;
		
		Handle m_RendererID;
	};
}