#include "pen_tool.hpp"

namespace pixee
{
	PenTool::PenTool(Canvas& canvas)
		: Tool("Pen", ToolType::Pen, canvas)
	{

	}

	void PenTool::update()
	{
		if (!m_IsDrawing)
			return;

		glm::ivec2 currentPixelPos;

		if (!m_Canvas.mouseToCanvasPosition(m_MousePosition, currentPixelPos))
			return;

		UILayer* uiLayer = core::Application::getInstance().getLayer<UILayer>();
		ui::ColorPickerPanel& colorPicker = uiLayer->getColorPickerPanel();
		m_CurrentColor = colorPicker.getSelectedColor();

		const uint32_t newPixelColor = utils::ARGB(
			static_cast<uint32_t>(m_CurrentColor.r * 255),
			static_cast<uint32_t>(m_CurrentColor.g * 255),
			static_cast<uint32_t>(m_CurrentColor.b * 255),
			static_cast<uint32_t>(m_CurrentColor.a * 255)
		);

		if (m_FirstClick)
		{
			placePixel(currentPixelPos, newPixelColor);
			m_LastCanvasPixelPos = currentPixelPos;
			m_FirstClick = false;
		}
		else
		{
			drawLine(
				m_LastCanvasPixelPos.x,
				m_LastCanvasPixelPos.y,
				currentPixelPos.x,
				currentPixelPos.y,
				newPixelColor
			);
			m_LastCanvasPixelPos = currentPixelPos;
		}
	}

	void PenTool::render()
	{
		glm::ivec2 placeholderPixelPos;
		if (!m_Canvas.mouseToCanvasPosition(m_MousePosition, placeholderPixelPos))
			return;

		SDL_Renderer* renderer = core::Application::getInstance().getRenderer();

		int screenX = static_cast<int>(m_Canvas.getPosition().x) + (placeholderPixelPos.x * m_Canvas.getZoom());
		int screenY = static_cast<int>(m_Canvas.getPosition().y) + (placeholderPixelPos.y * m_Canvas.getZoom());

		SDL_Rect placeholderPixelRect = {
			.x = screenX,
			.y = screenY,
			.w = m_Canvas.getZoom(),
			.h = m_Canvas.getZoom()
		};

		UILayer* uiLayer = core::Application::getInstance().getLayer<UILayer>();
		ui::ColorPickerPanel& colorPicker = uiLayer->getColorPickerPanel();
		glm::vec4 activeColor = colorPicker.getSelectedColor();

		SDL_SetRenderDrawColor(
			renderer,
			static_cast<uint8_t>(activeColor.r * 255),
			static_cast<uint8_t>(activeColor.g * 255),
			static_cast<uint8_t>(activeColor.b * 255),
			static_cast<uint8_t>(activeColor.a * 255)
		);
		SDL_RenderFillRect(renderer, &placeholderPixelRect);
	}

	bool PenTool::onMouseButtonDown(event::MouseButtonDownEvent& e)
	{
		if (e.getButton() == event::MouseButton::Left)
		{
			m_IsDrawing = true;
			return true;
		}

		return false;
	}

	bool PenTool::onMouseButtonReleased(event::MouseButtonReleasedEvent& e)
	{
		if (e.getButton() == event::MouseButton::Left)
		{
			m_IsDrawing = false;
			m_FirstClick = true;
		}

		return false;
	}
}