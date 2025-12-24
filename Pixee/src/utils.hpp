#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>

#include <vec2.hpp>
#include <vec4.hpp>

namespace pixee
{
	namespace utils
	{
		inline constexpr uint32_t ARGB(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
		{
			return (a << 24) | (r << 16) | (g << 8) | b;
		}

		inline constexpr uint32_t ARGB(const glm::vec4& rgba)
		{
			return ARGB(rgba.r, rgba.g, rgba.b, rgba.a);
		}

		inline glm::vec4 toRGBA(uint32_t argb)
		{
			uint8_t a = (argb >> 24) & 0xFF;
			uint8_t r = (argb >> 16) & 0xFF;
			uint8_t g = (argb >> 8) & 0xFF;
			uint8_t b = argb & 0xFF;

			return glm::vec4(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
		}

		inline glm::ivec2 absVec2Int(glm::ivec2 value)
		{
			int x = static_cast<int>(std::abs(value.x));
			int y = static_cast<int>(std::abs(value.y));

			return glm::ivec2(x, y);
		}
	}
}

#endif