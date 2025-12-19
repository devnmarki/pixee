#include "pen_tool.hpp"

namespace pixee
{
	PenTool::PenTool(Canvas& canvas)
		: Tool(ToolType::Pen, canvas)
	{

	}

	void PenTool::update()
	{
		if (!m_IsDrawing)
			return;

		glm::ivec2 currentPixelPos;

		if (!m_Canvas.mouseToCanvasPosition(m_MousePosition, currentPixelPos))
			return;

		UILayer* uiLayer = core::Application::getInstance().getLayer<UILayer>();
		ui::ColorPickerPanel& colorPicker = uiLayer->getColorPickerPanel();
		glm::vec4 newColor = colorPicker.getSelectedColor();

		const uint32_t newPixelColor = utils::ARGB(
			static_cast<uint32_t>(newColor.r * 255),
			static_cast<uint32_t>(newColor.g * 255),
			static_cast<uint32_t>(newColor.b * 255),
			static_cast<uint32_t>(newColor.a * 255)
		);

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

	bool PenTool::onMouseButtonDown(event::MouseButtonDownEvent& e)
	{
		if (e.getButton() == event::MouseButton::Left)
		{
			m_IsDrawing = true;
			return true;
		}

		return false;
	}

	bool PenTool::onMouseButtonReleased(event::MouseButtonReleasedEvent& e)
	{
		if (e.getButton() == event::MouseButton::Left)
		{
			m_IsDrawing = false;
			m_FirstClick = true;
		}

		return false;
	}

	void PenTool::placePixel(const glm::ivec2& pixelPos, uint32_t color)
	{
		if (m_Canvas.pixelAlreadyExists(pixelPos, color))
			return;

		m_Canvas.setPixel(pixelPos, color);
	}

	void PenTool::drawLine(int x0, int y0, int x1, int y1, uint32_t color)
	{
		int dx = std::abs(x1 - x0);
		int dy = -std::abs(y1 - y0);
		int sx = x0 < x1 ? 1 : -1;
		int sy = y0 < y1 ? 1 : -1;
		int err = dx + dy;

		while (true) {
			placePixel(glm::ivec2(x0, y0), color);

			if (x0 == x1 && y0 == y1) break;

			int e2 = 2 * err;
			if (e2 >= dy) {
				err += dy;
				x0 += sx;
			}
			if (e2 <= dx) {
				err += dx;
				y0 += sy;
			}
		}
	}
}