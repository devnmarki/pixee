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
		virtual ~PenTool() = default;

		void update() override;
		void render() override;

		bool onMouseButtonDown(event::MouseButtonDownEvent& e) override;
		bool onMouseButtonReleased(event::MouseButtonReleasedEvent& e) override;

	private:
		bool m_IsDrawing = false;
		bool m_FirstClick = true;
		glm::vec2 m_LastCanvasPixelPos{ 0, 0 };
		glm::vec4 m_CurrentColor{ 0, 0, 0, 0 };
	};
}

#endif