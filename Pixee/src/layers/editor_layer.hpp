#ifndef EDITORLAYER_HPP
#define EDITORLAYER_HPP

#include <print>

#include <vec2.hpp>

#include "core.hpp"
#include "utils.hpp"
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
		bool onMouseDown(event::MouseButtonDownEvent& e);
		bool onMouseMoved(event::MouseMovedEvent& e);

		void placePixel(const glm::ivec2& pixelPos, uint32_t color);
		void erasePixel(const glm::ivec2& pixelPos);

	private:
		std::unique_ptr<Canvas> m_Canvas;

		glm::dvec2 m_MousePosition;
	};
}

#endif