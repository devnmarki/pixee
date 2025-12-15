#ifndef EDITORLAYER_HPP
#define EDITORLAYER_HPP

#include <print>

#include <vec2.hpp>

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
		bool onMousePress(event::MouseButtonPressedEvent& e);
		bool onMouseMoved(event::MouseMovedEvent& e);

	private:
		std::unique_ptr<Canvas> m_Canvas;

		glm::dvec2 m_MousePosition;
	};
}

#endif