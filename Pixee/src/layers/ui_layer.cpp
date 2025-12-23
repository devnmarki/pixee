#include "ui_layer.hpp"

#include "layers/editor_layer.hpp"

namespace pixee
{
	UILayer::UILayer()
		: m_ColorPickerPanel(), m_MenuBar()
	{
		m_EditorLayer = core::Application::getInstance().getLayer<EditorLayer>();
		m_ToolsPanel = std::make_shared<ui::ToolsPanel>(m_EditorLayer->getCanvas());
	}

	void UILayer::onEvent(event::Event& e)
	{
		event::EventDispatcher dispatcher(e);
		dispatcher.dispatch<event::MouseButtonDownEvent>([this](event::MouseButtonDownEvent& e) { return onMouseDown(e); });
	}

	void UILayer::onGuiRender()
	{
		m_ColorPickerPanel.render();
		m_ToolsPanel->render(m_EditorLayer->getActiveToolPtr(), [this](std::shared_ptr<Tool> newTool) {
			m_EditorLayer->setActiveTool(newTool);
		});
		m_MenuBar.render();
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