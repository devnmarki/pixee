#ifndef CHECKER_TEXTURE_HPP
#define CHECKER_TEXTURE_HPP

#include <vec2.hpp>

#include "core.hpp"

namespace pixee
{
	namespace gfx
	{
		class CheckerTexture
		{
		public:
			CheckerTexture(int cellSize, uint32_t colorA, uint32_t colorB);
			~CheckerTexture();

			void draw(const glm::vec2& position, int width, int height);

		private:
			SDL_Texture* m_Handle;
			int m_CellSize;
		};
	}
}

#endif