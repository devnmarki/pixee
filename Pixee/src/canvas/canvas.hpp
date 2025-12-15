#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <vector>

#include <SDL.h>
#include <vec2.hpp>

#include "core.hpp"

namespace pixee
{
	class Canvas
	{
	public:
		Canvas(int width, int height);
		~Canvas();

		void upload();
		void render();

		void setPixel(const glm::ivec2& position, uint32_t color);

		bool mouseToCanvasPosition(const glm::dvec2& position, glm::ivec2& out) const;

	private:
		int m_Width;
		int m_Height;
		glm::vec2 m_Position;
		int m_Zoom;

		SDL_Texture* m_PixelsTexture;
		std::vector<uint32_t> m_PixelBuffer;
	};
}

#endif