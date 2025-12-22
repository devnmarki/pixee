#include "eraser_tool.hpp"

namespace pixee
{
	EraserTool::EraserTool(Canvas& canvas)
		: Tool("Eraser", ToolType::Eraser, canvas)
	{

	}

	void EraserTool::update()
	{
		if (!m_IsErasing)
			return;

		glm::ivec2 currentPixelPos;

		if (!m_Canvas.mouseToCanvasPosition(m_MousePosition, currentPixelPos))
			return;

		const uint32_t newPixelColor = 0x00000000;

		if (m_FirstClick)
		{
			placePixel(currentPixelPos, newPixelColor);
			m_LastCanvasPixelPos = currentPixelPos;
			m_FirstClick = false;
		}
		else
		{
			drawLine(
				m_LastCanvasPixelPos.x,
				m_LastCanvasPixelPos.y,
				currentPixelPos.x,
				currentPixelPos.y,
				newPixelColor
			);
			m_LastCanvasPixelPos = currentPixelPos;
		}
	}

	void EraserTool::render()
	{
		glm::ivec2 placeholderPos;
		if (!m_Canvas.mouseToCanvasPosition(m_MousePosition, placeholderPos))
			return;

		int screenX = static_cast<int>(m_Canvas.getPosition().x) + (placeholderPos.x * m_Canvas.getZoom());
		int screenY = static_cast<int>(m_Canvas.getPosition().y) + (placeholderPos.y * m_Canvas.getZoom());
		SDL_Rect placeholderRect = { screenX, screenY, m_Canvas.getZoom(), m_Canvas.getZoom() };
		SDL_Renderer* renderer = core::Application::getInstance().getRenderer();

		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderDrawRect(renderer, &placeholderRect);
	}

	bool EraserTool::onMouseButtonDown(event::MouseButtonDownEvent& e)
	{
		if (e.getButton() == event::MouseButton::Left)
		{
			m_IsErasing = true;
			return true;
		}

		return false;
	}

	bool EraserTool::onMouseButtonReleased(event::MouseButtonReleasedEvent& e)
	{
		if (e.getButton() == event::MouseButton::Left)
		{
			m_IsErasing = false;
			m_FirstClick = true;
		}

		return false;
	}
}