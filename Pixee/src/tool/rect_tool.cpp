#include "rect_tool.hpp"
#include "layers/ui_layer.hpp"

namespace pixee
{
	RectTool::RectTool(Canvas& canvas)
		: Tool("Rect", ToolType::Rect, canvas)
	{
	}

	void RectTool::update()
	{
		if (!m_Dragging)
			return;

		glm::ivec2 mp;
		if (!m_Canvas.mouseToCanvasPosition(m_MousePosition, mp))
			return;

		m_RectEndPos = mp;
	}

	void RectTool::render()
	{
		if (!m_Dragging)
			return;

		core::Application& app = core::Application::getInstance();
		SDL_Renderer* renderer = app.getRenderer();

		glm::ivec2 topLeft = glm::min(m_RectStartPos, m_RectEndPos);
		glm::ivec2 bottomRight = glm::max(m_RectStartPos, m_RectEndPos);
		glm::ivec2 size = bottomRight - topLeft + glm::ivec2(1, 1);

		int screenX = static_cast<int>(m_Canvas.getPosition().x) + (topLeft.x * m_Canvas.getZoom());
		int screenY = static_cast<int>(m_Canvas.getPosition().y) + (topLeft.y * m_Canvas.getZoom());
		int screenW = size.x * m_Canvas.getZoom();
		int screenH = size.y * m_Canvas.getZoom();

		SDL_Rect dragRect = { screenX, screenY, screenW, screenH };

		glm::vec4 currentColor = app.getLayer<UILayer>()->getColorPickerPanel().getSelectedColor();
		SDL_SetRenderDrawColor(
			renderer,
			static_cast<uint8_t>(currentColor.r * 255),
			static_cast<uint8_t>(currentColor.g * 255),
			static_cast<uint8_t>(currentColor.b * 255),
			static_cast<uint8_t>(currentColor.a * 255)
		);
		SDL_RenderDrawRect(renderer, &dragRect);
	}

	bool RectTool::onMouseButtonPressed(event::MouseButtonPressedEvent& e)
	{
		if (e.getButton() == event::MouseButton::Left)
		{
			if (!m_Canvas.mouseToCanvasPosition(m_MousePosition, m_RectStartPos))
				return false;

			m_RectEndPos = m_RectStartPos;
			m_Dragging = true;
		}
		return false;
	}

	bool RectTool::onMouseButtonReleased(event::MouseButtonReleasedEvent& e)
	{
		if (e.getButton() == event::MouseButton::Left && m_Dragging)
		{
			m_Dragging = false;

			drawRectangle();
		}
		return false;
	}

	void RectTool::drawRectangle()
	{
		UILayer* uiLayer = core::Application::getInstance().getLayer<UILayer>();
		glm::vec4 color = uiLayer->getColorPickerPanel().getSelectedColor();

		uint32_t argbColor = utils::ARGB(
			static_cast<uint8_t>(color.r * 255),
			static_cast<uint8_t>(color.g * 255),
			static_cast<uint8_t>(color.b * 255),
			static_cast<uint8_t>(color.a * 255)
		);

		glm::ivec2 topLeft = glm::min(m_RectStartPos, m_RectEndPos);
		glm::ivec2 bottomRight = glm::max(m_RectStartPos, m_RectEndPos);

		for (int x = topLeft.x; x <= bottomRight.x; x++)
		{
			m_Canvas.setPixel(glm::ivec2(x, topLeft.y), argbColor);
			m_Canvas.setPixel(glm::ivec2(x, bottomRight.y), argbColor);
		}

		for (int y = topLeft.y; y <= bottomRight.y; y++)
		{
			m_Canvas.setPixel(glm::ivec2(topLeft.x, y), argbColor);
			m_Canvas.setPixel(glm::ivec2(bottomRight.x, y), argbColor);
		}
	}
}