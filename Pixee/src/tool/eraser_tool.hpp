#ifndef ERASER_TOOL_HPP
#define ERASER_TOOL_HPP

#include "tool/tool.hpp"

namespace pixee
{
	class EraserTool : public Tool
	{
	public:
		EraserTool(Canvas& canvas);
	
		void update() override;
		void render() override;

		bool onMouseButtonDown(event::MouseButtonDownEvent& e) override;
		bool onMouseButtonReleased(event::MouseButtonReleasedEvent& e) override;

	private:
		bool m_IsErasing = false;
		bool m_FirstClick = true;

		glm::vec2 m_LastCanvasPixelPos{ 0, 0 };
	};
}

#endif