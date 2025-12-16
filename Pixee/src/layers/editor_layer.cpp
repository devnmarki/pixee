#include "editor_layer.hpp"

namespace pixee
{
	EditorLayer::EditorLayer()
		: m_MousePosition(0, 0)
	{
		glm::vec2 canvasPosition;
		canvasPosition.x = core::Application::getInstance().getWindow()->getWidth() / 2 - 32 * 8;
		canvasPosition.y = core::Application::getInstance().getWindow()->getHeight() / 2 - 32 * 8;
		m_Canvas = std::make_unique<Canvas>(64, 64, canvasPosition);
	}

	void EditorLayer::onUpdate()
	{
		if (!m_IsDrawing) 
			return;

		glm::ivec2 newPixelPos;
		constexpr uint32_t newPixelColor = utils::ARGB(255, 0, 0, 255);

		if (!m_Canvas->mouseToCanvasPosition(m_MousePosition, newPixelPos))
			return;

		placePixel(newPixelPos, newPixelColor);
	}

	void EditorLayer::onRender()
	{
		m_Canvas->render();
	}

	void EditorLayer::onEvent(event::Event& event)
	{
		event::EventDispatcher dispatcher(event);
		dispatcher.dispatch<event::MouseButtonPressedEvent>([this](event::MouseButtonPressedEvent& e) { return onMousePress(e); });
		dispatcher.dispatch<event::MouseButtonReleasedEvent>([this](event::MouseButtonReleasedEvent& e) { return onMouseReleased(e); });
		dispatcher.dispatch<event::MouseButtonDownEvent>([this](event::MouseButtonDownEvent& e) { return onMouseDown(e); });
		dispatcher.dispatch<event::MouseMovedEvent>([this](event::MouseMovedEvent& e) { return onMouseMoved(e); });
	}

	bool EditorLayer::onMousePress(event::MouseButtonPressedEvent& e)
	{
		return false;
	}

	bool EditorLayer::onMouseReleased(event::MouseButtonReleasedEvent& e)
	{
		if (e.getButton() == event::MouseButton::Left)
			m_IsDrawing = false;

		return false;
	}

	bool EditorLayer::onMouseDown(event::MouseButtonDownEvent& e)
	{
		glm::ivec2 newPixelPos;
		bool inCanvas = m_Canvas->mouseToCanvasPosition(m_MousePosition, newPixelPos);

		if (e.getButton() == event::MouseButton::Left)
			m_IsDrawing = true;

		if (e.getButton() == event::MouseButton::Right && inCanvas)
			erasePixel(newPixelPos);

		return false;
	}

	bool EditorLayer::onMouseMoved(event::MouseMovedEvent& e)
	{
		m_MousePosition.x = e.getX();
		m_MousePosition.y = e.getY();

		return false;
	}

	void EditorLayer::placePixel(const glm::ivec2& pixelPos, uint32_t color)
	{
		if (m_Canvas->pixelWithSameColor(pixelPos, color))
			return;

		std::println("Pixel placed at position X: {}, Y: {}", pixelPos.x, pixelPos.y);

		m_Canvas->setPixel(pixelPos, color);
	}

	void EditorLayer::erasePixel(const glm::ivec2& pixelPos)
	{
		if (m_Canvas->pixelWithSameColor(pixelPos, m_Canvas->getBackgroundColor()))
			return;

		std::println("Pixel erased at position X: {}, Y: {}", pixelPos.x, pixelPos.y);

		m_Canvas->setPixel(pixelPos, m_Canvas->getBackgroundColor()); 
	}
}