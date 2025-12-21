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

		bool onKeyPressed(event::KeyPressedEvent& e) override;

		bool onMouseButtonPressed(event::MouseButtonPressedEvent& e) override;
		bool onMouseButtonReleased(event::MouseButtonReleasedEvent& e) override;

	private:
		void drawRectangle();
		void fillRectangle();

	private:
		bool m_Dragging = false;
		glm::ivec2 m_RectStartPos{ 0, 0 };
		glm::ivec2 m_RectEndPos{ 0, 0 };
		bool m_FillMode = false;
	};
}

#endif