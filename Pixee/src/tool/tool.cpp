#include "tool.hpp"

#include "layers/editor_layer.hpp"

namespace pixee
{
	Tool::Tool(const std::string& name, ToolType toolType, Canvas& canvas)
		: m_Name(name), m_ToolType(toolType), m_Canvas(canvas)
	{
		
	}

	bool Tool::onMouseMoved(event::MouseMovedEvent& e)
	{
		m_MousePosition.x = e.getX();
		m_MousePosition.y = e.getY();

		return false;
	}

	void Tool::placePixel(const glm::ivec2& pixelPos, uint32_t color)
	{
		if (m_Canvas.pixelAlreadyExists(pixelPos, color))
			return;

		m_Canvas.setPixel(pixelPos, color);
	}

	void Tool::drawLine(int x0, int y0, int x1, int y1, uint32_t color)
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