#ifndef PEN_TOOL_HPP
#define PEN_TOOL_HPP

#include "tool/tool.hpp"
#include "layers/ui_layer.hpp"
#include "ui/color_picker_panel.hpp"
#include "utils.hpp"

namespace pixee
{
	class PenTool : public Tool
	{
	public:
		PenTool(Canvas& canvas);

		void update() override;

		bool onMouseButtonDown(event::MouseButtonDownEvent& e) override;
		bool onMouseButtonReleased(event::MouseButtonReleasedEvent& e) override;

	protected:
		void placePixel(const glm::ivec2& pixelPos, uint32_t color);
		void drawLine(int x0, int y0, int x1, int y1, uint32_t color);

	private:
		bool m_IsDrawing = false;
		bool m_FirstClick = true;

		glm::vec2 m_LastCanvasPixelPos{ 0, 0 };
	};
}

#endif