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