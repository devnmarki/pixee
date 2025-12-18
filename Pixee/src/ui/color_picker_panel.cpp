#include "color_picker_panel.hpp"

namespace pixee
{
	namespace ui
	{
		ColorPickerPanel::ColorPickerPanel()
		{

		}

		void ColorPickerPanel::render()
		{
			ImGui::Begin("Color Picker");

			ImGui::ColorPicker4("", m_SelectedColor);

			ImGui::End();
		}

		glm::vec4 ColorPickerPanel::getSelectedColor() const
		{
			return glm::vec4(m_SelectedColor[0], m_SelectedColor[1], m_SelectedColor[2], m_SelectedColor[3]);
		}
	}
}