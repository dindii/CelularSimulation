#include <stdint.h>
#include <Math/vec4.h>

namespace CS
{
	static uint32_t Get1DIndexFrom2DArray(uint32_t x, uint32_t y, uint32_t width)
	{
		return (y * width + x);
	}

	static vec4<uint8_t> ColorFloatToByte(const vec4<float>& color)
	{
		return vec4<uint8_t>(
			::roundf(color.r * 255.0),
			::roundf(color.g * 255.0),
			::roundf(color.b * 255.0),
			::roundf(color.a * 255.0)
		);		
	}
}