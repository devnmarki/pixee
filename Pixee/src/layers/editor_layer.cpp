#include "editor_layer.hpp"

namespace pixee
{
	void EditorLayer::onAttach()
	{
		std::cout << "EditorLayer attached!" << std::endl;
	}

	void EditorLayer::onUpdate()
	{

	}

	void EditorLayer::onEvent(event::Event& event)
	{
		event::EventDispatcher dispatcher(event);
		dispatcher.dispatch<event::KeyPressedEvent>([this](event::KeyPressedEvent& e) { return onKeyPressedEvent(e); });
		dispatcher.dispatch<event::KeyReleasedEvent>([this](event::KeyReleasedEvent& e) { return onKeyReleasedEvent(e); });
		dispatcher.dispatch<event::KeyDownEvent>([this](event::KeyDownEvent& e) { return onKeyDownEvent(e); });
		dispatcher.dispatch<event::MouseButtonPressedEvent>([this](event::MouseButtonPressedEvent& e) { return onMouseButtonPressedEvent(e); });
		dispatcher.dispatch<event::MouseButtonReleasedEvent>([this](event::MouseButtonReleasedEvent& e) { return onMouseButtonReleasedEvent(e); });
		dispatcher.dispatch<event::MouseButtonDownEvent>([this](event::MouseButtonDownEvent& e) { return onMouseButtonDownEvent(e); });
	}
	
	bool EditorLayer::onKeyPressedEvent(event::KeyPressedEvent& e)
	{
		if (e.getKeyCode() == SDLK_a)
			std::println("a pressed");

		return false;
	}

	bool EditorLayer::onKeyReleasedEvent(event::KeyReleasedEvent& e)
	{
		if (e.getKeyCode() == SDLK_d)
			std::println("d released");

		return false;
	}

	bool EditorLayer::onKeyDownEvent(event::KeyDownEvent& e)
	{
		if (e.getKeyCode() == SDLK_w)
			std::println("w down");

		return false;
	}

	bool EditorLayer::onMouseButtonPressedEvent(event::MouseButtonPressedEvent& e)
	{
		if (e.getButton() == event::MouseButton::Left)
			std::println("left mouse button clicked :)");

		return false;
	}

	bool EditorLayer::onMouseButtonReleasedEvent(event::MouseButtonReleasedEvent& e)
	{
		if (e.getButton() == event::MouseButton::Right)
			std::println("right mouse button released :(");

		return false;
	}

	bool EditorLayer::onMouseButtonDownEvent(event::MouseButtonDownEvent& e)
	{
		if (e.getButton() == event::MouseButton::Middle)
			std::println("scroll is being held :|");

		return false;
	}
}