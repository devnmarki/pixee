#ifndef RECT_TOOL_HPP
#define RECT_TOOL_HPP

#include <print>

#include "tool/tool.hpp"
#include "utils.hpp"

#include <glm.hpp>

namespace pixee
{
	class RectTool : public Tool
	{
	public:
		RectTool(Canvas& canvas);

		void update() override;
		void render() override;

		bool onMouseButtonPressed(event::MouseButtonPressedEvent& e) override;
		bool onMouseButtonReleased(event::MouseButtonReleasedEvent& e) override;

	private:
		void drawRectangle();

	private:
		bool m_Dragging = false;
		glm::ivec2 m_RectStartPos{ 0, 0 };
		glm::ivec2 m_RectEndPos{ 0, 0 };
	};
}

#endif