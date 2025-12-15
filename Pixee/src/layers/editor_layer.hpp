#ifndef EDITORLAYER_HPP
#define EDITORLAYER_HPP

#include <print>

#include "core.hpp"

#include "canvas/canvas.hpp"

namespace pixee
{
	class EditorLayer : public core::Layer
	{
	public:
		EditorLayer();

		void onRender() override;
		void onEvent(event::Event& event) override;

	private:
		//bool onKeyPressedEvent(event::KeyPressedEvent& e);
		//bool onKeyReleasedEvent(event::KeyReleasedEvent& e);
		//bool onKeyDownEvent(event::KeyDownEvent& e);

		//bool onMouseButtonPressedEvent(event::MouseButtonPressedEvent& e);
		//bool onMouseButtonReleasedEvent(event::MouseButtonReleasedEvent& e);
		//bool onMouseButtonDownEvent(event::MouseButtonDownEvent& e);
		//bool onMouseMovedEvent(event::MouseMovedEvent& e);

	private:
		Canvas m_Canvas;
	};
}

#endif