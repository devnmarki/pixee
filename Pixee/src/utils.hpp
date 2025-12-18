#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

namespace pixee
{
	namespace utils
	{
		inline constexpr uint32_t ARGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			return (a << 24) | (r << 16) | (g << 8) | b;
		}
	}
}

#endif