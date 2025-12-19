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
		glm::vec4 newColor = colorPicker.getSelectedColor();

		const uint32_t newPixelColor = utils::ARGB(
			static_cast<uint32_t>(newColor.r * 255),
			static_cast<uint32_t>(newColor.g * 255),
			static_cast<uint32_t>(newColor.b * 255),
			static_cast<uint32_t>(newColor.a * 255)
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