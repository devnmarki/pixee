#include "ui_layer.hpp"
#include "ui_layer.hpp"
#include "ui_layer.hpp"
#include "ui_layer.hpp"
#include "ui_layer.hpp"

namespace pixee
{
	UILayer::UILayer()
		: m_ColorPickerPanel()
	{
		
	}

	void UILayer::onEvent(event::Event& e)
	{
		event::EventDispatcher dispatcher(e);
		dispatcher.dispatch<event::MouseButtonDownEvent>([this](event::MouseButtonDownEvent& e) { return onMouseDown(e); });
	}

	void UILayer::onGuiRender()
	{
		m_ColorPickerPanel.render();

		//ImGui::ShowDemoWindow();
	}

	ui::ColorPickerPanel& UILayer::getColorPickerPanel()
	{
		return m_ColorPickerPanel;
	}

	bool UILayer::isHoveringUI()
	{
		ImGuiIO& io = ImGui::GetIO();
		return io.WantCaptureMouse;
	}

	bool pixee::UILayer::onMouseDown(event::MouseButtonDownEvent& e)
	{
		if (isHoveringUI())
			return true;

		return false;
	}
}