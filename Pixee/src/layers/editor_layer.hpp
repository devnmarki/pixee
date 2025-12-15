#ifndef EDITORLAYER_HPP
#define EDITORLAYER_HPP

#include <print>

#include "core.hpp"

namespace pixee
{
	class EditorLayer : public core::Layer
	{
	public:
		EditorLayer() = default;

		void onAttach() override;
		void onUpdate() override;
		void onEvent(event::Event& event) override;

	private:
		bool onKeyPressedEvent(event::KeyPressedEvent& e);
		bool onKeyReleasedEvent(event::KeyReleasedEvent& e);
		bool onKeyDownEvent(event::KeyDownEvent& e);

		bool onMouseButtonPressedEvent(event::MouseButtonPressedEvent& e);
		bool onMouseButtonReleasedEvent(event::MouseButtonReleasedEvent& e);
		bool onMouseButtonDownEvent(event::MouseButtonDownEvent& e);
	};
}

#endif