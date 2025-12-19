#include "tool.hpp"

#include "layers/editor_layer.hpp"

namespace pixee
{
	Tool::Tool(ToolType toolType, Canvas& canvas)
		: m_ToolType(toolType), m_Canvas(canvas)
	{
		
	}

	bool Tool::onMouseMoved(event::MouseMovedEvent& e)
	{
		m_MousePosition.x = e.getX();
		m_MousePosition.y = e.getY();

		return false;
	}
}