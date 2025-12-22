#include "color_picker_tool.hpp"

namespace pixee
{
	ColorPickerTool::ColorPickerTool(Canvas& canvas)
		: Tool("Color Picker", ToolType::ColorPicker, canvas)
	{

	}

	void ColorPickerTool::update()
	{
		
	}

	bool ColorPickerTool::onMouseButtonDown(event::MouseButtonDownEvent& e)
	{
		glm::ivec2 targetPixelPos;
		m_Canvas.mouseToCanvasPosition(m_MousePosition, targetPixelPos);

		UILayer* uiLayer = core::Application::getInstance().getLayer<UILayer>();
		uint32_t targetPixel = m_Canvas.getPixel(targetPixelPos);

		if (uiLayer->getColorPickerPanel().getSelectedColor() == utils::toRGBA(targetPixel))
			return false;
		
		std::println("Target Pixel: {}", targetPixel);

		if (e.getButton() == event::MouseButton::Left)
		{
			uiLayer->getColorPickerPanel().setSelectedColor(targetPixel);
		}

		return false;
	}
}