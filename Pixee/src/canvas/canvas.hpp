#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <vector>

#include <SDL.h>

#include "core.hpp"

namespace pixee
{
	class Canvas
	{
	public:
		Canvas(int width, int height);

		void upload();
		void render();

	private:
		int m_Width;
		int m_Height;

		SDL_Texture* m_PixelsTexture;
		std::vector<uint32_t> m_PixelBuffer;
	};
}

#endif