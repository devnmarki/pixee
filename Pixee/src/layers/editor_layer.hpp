#ifndef EDITORLAYER_HPP
#define EDITORLAYER_HPP

#include <print>

#include <vec2.hpp>

#include "core.hpp"
#include "utils.hpp"
#include "canvas/canvas.hpp"
#include "graphics/checker_texture.hpp"

namespace pixee
{
	class EditorLayer : public core::Layer
	{
	public:
		EditorLayer();

		void onUpdate() override;
		void onRender() override;
		void onEvent(event::Event& event) override;

	private:
		void handleDrawing();
		void handlePanning(event::MouseMovedEvent& e);
		void drawBackground();

		bool onKeyDown(event::KeyDownEvent& e);
		bool onKeyReleased(event::KeyReleasedEvent& e);

		bool onMousePress(event::MouseButtonPressedEvent& e);
		bool onMouseReleased(event::MouseButtonReleasedEvent& e);
		bool onMouseDown(event::MouseButtonDownEvent& e);
		bool onMouseMoved(event::MouseMovedEvent& e);

		void placePixel(const glm::ivec2& pixelPos, uint32_t color);
		void erasePixel(const glm::ivec2& pixelPos);

	private:
		std::unique_ptr<Canvas> m_Canvas;
		glm::vec2 m_CanvasPosition{0, 0};
		std::shared_ptr<gfx::CheckerTexture> m_CheckerTextureBG;

		glm::dvec2 m_MousePosition{0, 0};
		bool m_IsDrawing = false;

		glm::dvec2 m_MouseDelta{0, 0};
		bool m_IsPanning = false;
		glm::vec2 m_LastMousePosition{0, 0};
		glm::vec2 m_CanvasOffset{0, 0};
	};
}

#endif