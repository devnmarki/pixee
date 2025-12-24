#ifndef EDITOR_LAYER_HPP
#define EDITOR_LAYER_HPP

#include <print>
#include <algorithm>
#include <unordered_map>

#include <vec2.hpp>
#include <stb_image_write.h>
#include <stb_image.h>

#include "core.hpp"
#include "utils.hpp"
#include "canvas/canvas.hpp"
#include "graphics/checker_texture.hpp"
#include "layers/ui_layer.hpp"
#include "tool/pen_tool.hpp"
#include "tool/eraser_tool.hpp"

namespace pixee
{
	class EditorLayer : public core::Layer
	{
	public:
		EditorLayer();

		void onUpdate() override;
		void onRender() override;
		void onEvent(event::Event& event) override;

		void setActiveTool(std::shared_ptr<Tool> tool);

		Canvas& getCanvas() { return *m_Canvas; }
		const Canvas& getCanvas() const { return *m_Canvas; }
		std::shared_ptr<Tool> getActiveToolPtr() { return m_ActiveTool; }

	private:
		void handlePanning(event::MouseMovedEvent& e);
		void handleCanvasZooming(event::MouseScrolledEvent& e);
		
		void drawBackground();

		bool onKeyPressed(event::KeyPressedEvent& e);
		bool onKeyDown(event::KeyDownEvent& e);
		bool onKeyReleased(event::KeyReleasedEvent& e);

		bool onMousePress(event::MouseButtonPressedEvent& e);
		bool onMouseReleased(event::MouseButtonReleasedEvent& e);
		bool onMouseDown(event::MouseButtonDownEvent& e);
		bool onMouseMoved(event::MouseMovedEvent& e);
		bool onMouseScroll(event::MouseScrolledEvent& e);

		void setMenuBarContext(UILayer* uiLayer);
		void exportCanvasImage();
		void openImage();

	private:
		std::shared_ptr<Canvas> m_Canvas;
		glm::vec2 m_CanvasPosition{ 0, 0 };
		std::shared_ptr<gfx::CheckerTexture> m_CheckerTextureBG;

		glm::dvec2 m_MousePosition{ 0, 0 };

		glm::dvec2 m_MouseDelta{ 0, 0 };
		bool m_IsPanning = false;
		glm::vec2 m_LastMousePosition{ 0, 0 };
		glm::vec2 m_CanvasOffset{ 0, 0 };

		std::shared_ptr<Tool> m_ActiveTool;
		bool m_Initialized = false;
		std::unordered_map<SDL_Keycode, ToolType> m_ToolShortcutMap;
		std::shared_ptr<Tool> m_PreviousActiveTool;
		bool m_ColorPickerToolActive = false;
	};
}

#endif