#include "editor_layer.hpp"

namespace pixee
{
	void EditorLayer::onAttach()
	{
		std::cout << "EditorLayer attached!" << std::endl;
	}

	void EditorLayer::onUpdate()
	{
		//std::cout << "EditorLayer updating...\n";
	}

	void EditorLayer::onEvent(event::Event& event)
	{
		std::println("{}", event.toString());

		event::EventDispatcher dispatcher(event);
		dispatcher.dispatch<event::KeyPressedEvent>([this](event::KeyPressedEvent& e) { return onKeyPressedEvent(e); });
	}
	
	bool EditorLayer::onKeyPressedEvent(event::KeyPressedEvent& e)
	{
		if (e.getKeyCode() == SDLK_a)
			std::println("Moving left!");

		return false;
	}
}