#ifndef UI_LAYER_HPP
#define UI_LAYER_HPP

#include <imgui_internal.h>

#include "core.hpp"

#include "ui/color_picker_panel.hpp"

namespace pixee
{
	class UILayer : public core::Layer
	{
	public:
		UILayer();

		void onEvent(event::Event& e) override;
		void onGuiRender() override;

		ui::ColorPickerPanel& getColorPickerPanel();

	private:
		bool isHoveringUI();

		bool onMouseDown(event::MouseButtonDownEvent& e);

	private:
		ui::ColorPickerPanel m_ColorPickerPanel;
	};
}

#endif