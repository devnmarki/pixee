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
		Canvas(int width, int height, const glm::vec2& position = glm::vec2(0, 0));
		~Canvas();

		void upload();
		void render();
		void resize(int newWidth, int newHeight);

		void setPixel(const glm::ivec2& position, uint32_t color);
		bool pixelAlreadyExists(const glm::ivec2& position, uint32_t color);
		uint32_t getPixel(const glm::ivec2& position);

		bool mouseToCanvasPosition(const glm::dvec2& position, glm::ivec2& out) const;

		void setWidth(int width);
		void setHeight(int height);
		void setPosition(const glm::vec2& position);
		void setZoom(int zoom);

		int getWidth() const;
		int getHeight() const;
		glm::vec2 getPosition();
		uint32_t getBackgroundColor() const;
		int getZoom() const;
		SDL_Texture* getCanvasTexture();
		std::vector<uint32_t>& getPixels() { return m_PixelBuffer; }

	private:
		int m_Width;
		int m_Height;
		glm::vec2 m_Position;
		uint32_t m_BackgroundColor;
		int m_Zoom;

		SDL_Texture* m_PixelsTexture;
		std::vector<uint32_t> m_PixelBuffer;
	};
}

#endif