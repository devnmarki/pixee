#include "canvas.hpp"

namespace pixee
{
	Canvas::Canvas(int width, int height, const glm::vec2& position)
		: 
		m_Width(width), 
		m_Height(height), 
		m_Position(position),
		m_BackgroundColor(0x00000000),
		m_PixelBuffer(m_Width * m_Height, m_BackgroundColor), 
		m_Zoom(8)
	{
		m_PixelsTexture = SDL_CreateTexture(
			core::Application::getInstance().getRenderer(), 
			SDL_PIXELFORMAT_ARGB8888, 
			SDL_TEXTUREACCESS_STREAMING, 
			m_Width, 
			m_Height
		);

		SDL_SetTextureBlendMode(m_PixelsTexture, SDL_BLENDMODE_BLEND);
	}

	Canvas::~Canvas()
	{
		SDL_DestroyTexture(m_PixelsTexture);
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

		SDL_Rect dst = { m_Position.x, m_Position.y, m_Width * m_Zoom, m_Height * m_Zoom };
		SDL_RenderCopy(renderer, m_PixelsTexture, nullptr, &dst);
	}

	void Canvas::setPixel(const glm::ivec2& position, uint32_t color)
	{
		if (position.x < 0 || position.y < 0 || position.x >= m_Width || position.y >= m_Height)
			return;

		m_PixelBuffer[position.y * m_Width + position.x] = color;
	}

	bool Canvas::pixelAlreadyExists(const glm::ivec2& position, uint32_t color)
	{
		return m_PixelBuffer[position.y * m_Width + position.x] == color;
	}

	uint32_t Canvas::getPixel(const glm::ivec2& position)
	{
		return m_PixelBuffer[position.y * m_Width + position.x];
	}

	bool Canvas::mouseToCanvasPosition(const glm::dvec2& position, glm::ivec2& out) const
	{
		int canvasW = m_Width * m_Zoom;
		int canvasH = m_Height * m_Zoom;

		if (position.x < m_Position.x || position.y < m_Position.y)
			return false;

		if (position.x >= m_Position.x + canvasW || position.y >= m_Position.y + canvasH)
			return false;

		int localX = static_cast<int>(position.x) - m_Position.x;
		int localY = static_cast<int>(position.y) - m_Position.y;

		out.x = localX / m_Zoom;
		out.y = localY / m_Zoom;

		return true;
	}

	void Canvas::setPosition(const glm::vec2& position)
	{
		m_Position = position;
	}

	void Canvas::setZoom(int zoom)
	{
		m_Zoom = zoom;
	}

	int Canvas::getWidth() const
	{
		return m_Width;
	}

	int Canvas::getHeight() const
	{
		return m_Height;
	}

	glm::vec2 Canvas::getPosition()
	{
		return m_Position;
	}

	uint32_t Canvas::getBackgroundColor() const
	{
		return m_BackgroundColor;
	}

	int Canvas::getZoom() const
	{
		return m_Zoom;
	}

	SDL_Texture* Canvas::getCanvasTexture()
	{
		return m_PixelsTexture;
	}
}