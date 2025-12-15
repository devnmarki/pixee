#include "editor_layer.hpp"

namespace pixee
{
	EditorLayer::EditorLayer()
	{
		m_Canvas = std::make_unique<Canvas>(64, 64);
	}

	void EditorLayer::onRender()
	{
		m_Canvas->render();
	}

	void EditorLayer::onEvent(event::Event& event)
	{
		event::EventDispatcher dispatcher(event);
		dispatcher.dispatch<event::MouseButtonPressedEvent>([this](event::MouseButtonPressedEvent& e) { return onMousePress(e); });
		dispatcher.dispatch<event::MouseMovedEvent>([this](event::MouseMovedEvent& e) { return onMouseMoved(e); });
	}

	bool EditorLayer::onMousePress(event::MouseButtonPressedEvent& e)
	{
		glm::ivec2 newPixelPos;

		if (e.getButton() == event::MouseButton::Left && m_Canvas->mouseToCanvasPosition(m_MousePosition, newPixelPos))
		{
			std::println("Pixel placed at position X: {}, Y: {}", newPixelPos.x, newPixelPos.y);
			m_Canvas->setPixel(newPixelPos, 0xFF000000);
		}

		return false;
	}

	bool EditorLayer::onMouseMoved(event::MouseMovedEvent& e)
	{
		m_MousePosition.x = e.getX();
		m_MousePosition.y = e.getY();

		return false;
	}
}