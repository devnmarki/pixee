#include "canvas.hpp"

namespace pixee
{
	Canvas::Canvas(int width, int height)
		: m_Width(width), m_Height(height), m_PixelBuffer(m_Width * m_Height, 0xFF000000)
	{
		m_PixelsTexture = SDL_CreateTexture(
			core::Application::getInstance().getRenderer(), 
			SDL_PIXELFORMAT_RGBA8888, 
			SDL_TEXTUREACCESS_STREAMING, 
			m_Width, 
			m_Height
		);
	}

	void Canvas::upload()
	{
		SDL_UpdateTexture(
			m_PixelsTexture,
			nullptr,
			m_PixelBuffer.data(),
			m_Width * sizeof(uint32_t)
		);
	}

	void Canvas::render()
	{
		SDL_Renderer* renderer = core::Application::getInstance().getRenderer();

		upload();

		SDL_Rect dst = { 0, 0, m_Width * 8, m_Height * 8 };
		SDL_RenderCopy(renderer, m_PixelsTexture, nullptr, &dst);
	}
}