#include "checker_texture.hpp"

namespace pixee
{
	namespace gfx
	{
		CheckerTexture::CheckerTexture(int cellSize, uint32_t colorA, uint32_t colorB)
			: m_Handle(nullptr), m_CellSize(cellSize)
		{
			const int SIZE = cellSize * 2;
			std::vector<uint32_t> pixels(SIZE * SIZE);

			for (int y = 0; y < SIZE; y++)
			{
				for (int x = 0; x < SIZE; x++)
				{
					bool even = ((x / cellSize) + (y / cellSize)) % 2 == 0;

					pixels[y * SIZE + x] = even ? colorA : colorB;
				}
			}

			m_Handle = SDL_CreateTexture(
				core::Application::getInstance().getRenderer(),
				SDL_PIXELFORMAT_ARGB8888,
				SDL_TEXTUREACCESS_STATIC,
				SIZE,
				SIZE
			);

			SDL_UpdateTexture(
				m_Handle,
				nullptr,
				pixels.data(),
				SIZE * sizeof(uint32_t)
			);

			SDL_SetTextureBlendMode(m_Handle, SDL_BLENDMODE_BLEND);
		}
		
		CheckerTexture::~CheckerTexture()
		{
			SDL_DestroyTexture(m_Handle);
		}

		void CheckerTexture::draw(const glm::vec2& position, int width, int height)
		{
			SDL_Renderer* renderer = core::Application::getInstance().getRenderer();
			const int tileSize = m_CellSize * 8;

			for (int y = 0; y < height; y += tileSize)
			{
				for (int x = 0; x < width; x += tileSize)
				{
					SDL_Rect dst = {
						.x = static_cast<int>(position.x) + x,
						.y = static_cast<int>(position.y) + y,
						.w = tileSize,
						.h = tileSize
					};

					SDL_RenderCopy(renderer, m_Handle, nullptr, &dst);
				}
			}
		}
	}
}