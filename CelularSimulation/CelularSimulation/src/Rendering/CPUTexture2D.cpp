#pragma once
#include "CPUTexture2D.h"

namespace CS
{
	CPUTexture2D::CPUTexture2D(uint32_t width, uint32_t height, uint8_t nChannels, std::vector<uint8_t>&& initialData) noexcept : m_Width(width), m_Height(height), m_numChannels(nChannels)
	{
		uint32_t numPixels = width * height * nChannels;

		m_Pixels.reserve(numPixels);
		m_Pixels.resize(numPixels);

		if (initialData.size() > 0)
			memcpy(m_Pixels.data(), initialData.data(), numPixels * sizeof(uint8_t));
	}
	vec4<uint8_t> CPUTexture2D::GetPixel(uint32_t x, uint32_t y) const
	{
		vec4<uint8_t> color(0, 0, 0, 255);

		uint32_t arrayIdx = GetCoordinatesIndex(x, y) * m_numChannels;

		color.r = m_Pixels[arrayIdx++];
		color.g = m_Pixels[arrayIdx++];
		color.b = m_Pixels[arrayIdx++];
		color.a = m_Pixels[arrayIdx];

		return color;
	}
	void CPUTexture2D::SetPixel(uint32_t x, uint32_t y, vec4<uint8_t> color)
	{
		uint32_t arrayIdx = GetCoordinatesIndex(x, y) * m_numChannels;
		
		m_Pixels[arrayIdx++] = color.r;
		m_Pixels[arrayIdx++] = color.g;
		m_Pixels[arrayIdx++] = color.b;
		m_Pixels[arrayIdx]   = color.a;
	}

	uint32_t CPUTexture2D::GetCoordinatesIndex(uint32_t x, uint32_t y) const
	{
		return (y * m_Width + x);
	}
}
