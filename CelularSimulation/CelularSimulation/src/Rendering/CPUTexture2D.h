#pragma once

#include "Defines.h"
#include <Math/vec4.h>
#include <vector>

namespace CS
{
	class CPUTexture2D
	{
	public:
		CPUTexture2D(uint32_t width, uint32_t height, uint8_t nChannels, std::vector<uint8_t>&& initialData = std::vector<uint8_t>()) noexcept;
		std::vector<uint8_t>& GetPixels() { return m_Pixels; }
		
		
		void SetPixel(uint32_t x, uint32_t y, vec4<uint8_t> color);

		vec4<uint8_t> GetPixel(uint32_t x, uint32_t y) const;

		uint32_t GetSizeInBytes() const { return m_Width * m_Height * (uint32_t)m_numChannels * sizeof(uint8_t); }
		
		inline uint32_t GetWidth() const { return m_Width;}
		inline uint32_t GetHeight() const { return m_Height; }

	private:
		uint32_t GetCoordinatesIndex(uint32_t x, uint32_t y) const;

	private:
		std::vector<uint8_t> m_Pixels;
		
		uint32_t m_Width, m_Height;
		uint8_t m_numChannels;
		

	};
}