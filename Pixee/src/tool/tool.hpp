#ifndef TOOL_HPP
#define TOOL_HPP

#include "core.hpp"

#include "canvas/canvas.hpp"

namespace pixee
{
	enum class ToolType
	{
		Pen,
		Eraser
	};

	class Tool
	{
	public:
		virtual ~Tool() = default;

		virtual void update() { }
		virtual void render() { }

		virtual bool onMouseButtonPressed(event::MouseButtonPressedEvent& e) { return false; }
		virtual bool onMouseButtonReleased(event::MouseButtonReleasedEvent& e) { return false; }
		virtual bool onMouseButtonDown(event::MouseButtonDownEvent& e) { return false; }
		virtual bool onMouseMoved(event::MouseMovedEvent& e);

		ToolType getToolType() const { return m_ToolType; }
	
	protected:
		Tool(ToolType toolType, Canvas& canvas);

	protected:
		ToolType m_ToolType;
		Canvas& m_Canvas;

		glm::dvec2 m_MousePosition;
	};
}

#endif