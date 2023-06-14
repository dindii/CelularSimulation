#include <stdint.h>

namespace CS
{
	static uint32_t Get1DIndexFrom2DArray(uint32_t x, uint32_t y, uint32_t width)
	{
		return (y * width + x);
	}
}