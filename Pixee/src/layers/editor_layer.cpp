#include "editor_layer.hpp"

namespace pixee
{
	EditorLayer::EditorLayer()
		: m_Canvas(Canvas(64, 64))
	{

	}

	void EditorLayer::onRender()
	{
		m_Canvas.render();
	}

	void EditorLayer::onEvent(event::Event& event)
	{

	}
}