#ifndef UI_LAYER_HPP
#define UI_LAYER_HPP

#include <imgui_internal.h>

#include "core.hpp"

#include "ui/color_picker_panel.hpp"
#include "ui/tools_panel.hpp"
#include "ui/menu_bar.hpp"


namespace pixee
{
	class EditorLayer;

	class UILayer : public core::Layer
	{
	public:
		UILayer();

		void onEvent(event::Event& e) override;
		void onGuiRender() override;

		ui::ColorPickerPanel& getColorPickerPanel() { return m_ColorPickerPanel; }
		ui::ToolsPanel& getToolsPanel() { return *m_ToolsPanel; }
		ui::MenuBar& getMenuBar() { return m_MenuBar; }

	private:
		bool isHoveringUI();

		bool onMouseDown(event::MouseButtonDownEvent& e);

	private:
		ui::ColorPickerPanel m_ColorPickerPanel;
		std::shared_ptr<ui::ToolsPanel> m_ToolsPanel;
		ui::MenuBar m_MenuBar;

		EditorLayer* m_EditorLayer;
	};
}

#endif