#include "ui_layer.hpp"

#include "layers/editor_layer.hpp"

namespace pixee
{
	UILayer::UILayer()
		: m_ColorPickerPanel(), m_MenuBar(), m_InputContext()
	{
		m_EditorLayer = core::Application::getInstance().getLayer<EditorLayer>();
		m_ToolsPanel = std::make_shared<ui::ToolsPanel>(m_EditorLayer->getCanvas());
	}

	void UILayer::onEvent(event::Event& e)
	{
		event::EventDispatcher dispatcher(e);
		dispatcher.dispatch<event::KeyPressedEvent>([this](event::KeyPressedEvent& e) { return onKeyPressed(e); });
		dispatcher.dispatch<event::KeyReleasedEvent>([this](event::KeyReleasedEvent& e) { return onKeyReleased(e); });
		dispatcher.dispatch<event::KeyDownEvent>([this](event::KeyDownEvent& e) { return onKeyDown(e); });

		dispatcher.dispatch<event::MouseButtonDownEvent>([this](event::MouseButtonDownEvent& e) { return onMouseDown(e); });
	}

	void UILayer::onGuiRender()
	{
		m_ColorPickerPanel.render();
		m_ToolsPanel->render(m_EditorLayer->getActiveToolPtr(), [this](std::shared_ptr<Tool> newTool) {
			m_EditorLayer->setActiveTool(newTool);
		});
		m_MenuBar.render();

		//ImGui::ShowDemoWindow();
	}

	bool UILayer::onKeyPressed(event::KeyPressedEvent& e)
	{
		if (e.getKeyCode() == SDLK_e && m_InputContext.ctrlDown)
			m_MenuBar.getContext().onExportAsPNG();
		else if (e.getKeyCode() == SDLK_n && m_InputContext.ctrlDown)
			m_MenuBar.getContext().onNew();
		else if (e.getKeyCode() == SDLK_o && m_InputContext.ctrlDown)
			m_MenuBar.getContext().onOpen();

		return false;
	}

	bool UILayer::onKeyDown(event::KeyDownEvent& e)
	{
		if (e.getKeyCode() == SDLK_LCTRL)
			m_InputContext.ctrlDown = true;

		return false;
	}

	bool UILayer::onKeyReleased(event::KeyReleasedEvent& e)
	{
		if (e.getKeyCode() == SDLK_LCTRL)
			m_InputContext.ctrlDown = false;

		return false;
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