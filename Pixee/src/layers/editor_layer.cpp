#include "editor_layer.hpp"

namespace pixee
{
	EditorLayer::EditorLayer()
		: m_MousePosition(0), m_MouseDelta(0)
	{
		m_CanvasPosition.x = static_cast<float>(core::Application::getInstance().getWindow()->getWidth() / 2 - 32 * 8);
		m_CanvasPosition.y = static_cast<float>(core::Application::getInstance().getWindow()->getHeight() / 2 - 32 * 8);
		m_Canvas = std::make_unique<Canvas>(64, 64, m_CanvasPosition);
	}

	void EditorLayer::onUpdate()
	{
		if (m_IsPanning)
			m_IsDrawing = false;

		placePixels();
	}

	void EditorLayer::onRender()
	{
		m_Canvas->render();
	}

	void EditorLayer::onEvent(event::Event& event)
	{
		event::EventDispatcher dispatcher(event);
		dispatcher.dispatch<event::KeyDownEvent>([this](event::KeyDownEvent& e) { return onKeyDown(e); });
		dispatcher.dispatch<event::KeyReleasedEvent>([this](event::KeyReleasedEvent& e) { return onKeyReleased(e); });

		dispatcher.dispatch<event::MouseButtonPressedEvent>([this](event::MouseButtonPressedEvent& e) { return onMousePress(e); });
		dispatcher.dispatch<event::MouseButtonReleasedEvent>([this](event::MouseButtonReleasedEvent& e) { return onMouseReleased(e); });
		dispatcher.dispatch<event::MouseButtonDownEvent>([this](event::MouseButtonDownEvent& e) { return onMouseDown(e); });
		dispatcher.dispatch<event::MouseMovedEvent>([this](event::MouseMovedEvent& e) { return onMouseMoved(e); });
	}

	void EditorLayer::placePixels()
	{
		if (!m_IsDrawing)
			return;

		glm::ivec2 newPixelPos;
		constexpr uint32_t newPixelColor = utils::ARGB(255, 0, 0, 255);

		if (!m_Canvas->mouseToCanvasPosition(m_MousePosition, newPixelPos))
			return;

		placePixel(newPixelPos, newPixelColor);
	}

	bool EditorLayer::onKeyDown(event::KeyDownEvent& e)
	{
		//std::println("Key Pressed: {}", e.getKeyCode());

		return false;
	}

	bool EditorLayer::onKeyReleased(event::KeyReleasedEvent& e)
	{

		return false;
	}

	bool EditorLayer::onMousePress(event::MouseButtonPressedEvent& e)
	{
		if (e.getButton() == event::MouseButton::Middle)
		{
			m_IsPanning = true;
			m_LastMousePosition = m_MousePosition;

			SDL_Cursor* handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
			SDL_SetCursor(handCursor);

			return true;
		}

		return false;
	}

	bool EditorLayer::onMouseReleased(event::MouseButtonReleasedEvent& e)
	{
		if (e.getButton() == event::MouseButton::Left)
			m_IsDrawing = false;

		if (e.getButton() == event::MouseButton::Middle && m_IsPanning)
		{
			m_IsPanning = false;

			SDL_Cursor* arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
			SDL_SetCursor(arrowCursor);

			return true;
		}

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
		m_MouseDelta.x = e.getDeltaX();
		m_MouseDelta.y = e.getDeltaY();

		glm::vec2 currentMousePos;
		currentMousePos.x = static_cast<float>(e.getX());
		currentMousePos.y = static_cast<float>(e.getY());

		if (m_IsPanning)
		{
			float deltaX = currentMousePos.x - m_LastMousePosition.x;
			float deltaY = currentMousePos.y - m_LastMousePosition.y;

			m_CanvasPosition.x += deltaX;
			m_CanvasPosition.y += deltaY;

			m_Canvas->setPosition(m_CanvasPosition);
		}

		m_LastMousePosition = m_MousePosition;
		m_MousePosition = currentMousePos;

		return false;
	}

	void EditorLayer::placePixel(const glm::ivec2& pixelPos, uint32_t color)
	{
		if (m_Canvas->pixelAlreadyExists(pixelPos, color))
			return;

		m_Canvas->setPixel(pixelPos, color);
	}

	void EditorLayer::erasePixel(const glm::ivec2& pixelPos)
	{
		if (m_Canvas->pixelAlreadyExists(pixelPos, m_Canvas->getBackgroundColor()))
			return;

		m_Canvas->setPixel(pixelPos, m_Canvas->getBackgroundColor()); 
	}
}