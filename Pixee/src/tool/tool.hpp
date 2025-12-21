#ifndef TOOL_HPP
#define TOOL_HPP

#include "core.hpp"

#include "canvas/canvas.hpp"

namespace pixee
{
	enum class ToolType
	{
		Pen,
		Eraser,
		ColorPicker
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
		std::string getName() { return m_Name; }
	
	protected:
		Tool(const std::string& name, ToolType toolType, Canvas& canvas);

		void placePixel(const glm::ivec2& pixelPos, uint32_t color);
		void drawLine(int x0, int y0, int x1, int y1, uint32_t color);

	protected:
		ToolType m_ToolType;
		std::string m_Name;
		Canvas& m_Canvas;

		glm::dvec2 m_MousePosition{ 0, 0 };
	};
}

#endif