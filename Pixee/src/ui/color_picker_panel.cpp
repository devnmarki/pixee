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
			ImGui::Begin(WINDOW_ID.c_str());

			ImGui::ColorPicker4("##color_picker", m_SelectedColor);

			ImGui::End();
		}

		void ColorPickerPanel::setSelectedColor(const glm::vec4& newColor)
		{
			m_SelectedColor[0] = newColor.r;
			m_SelectedColor[1] = newColor.g;
			m_SelectedColor[2] = newColor.b;
			m_SelectedColor[3] = newColor.a;
		}

		void ColorPickerPanel::setSelectedColor(uint32_t argb)
		{
			glm::vec4 rgba = utils::toRGBA(argb);
			m_SelectedColor[0] = rgba.r;
			m_SelectedColor[1] = rgba.g;
			m_SelectedColor[2] = rgba.b;
			m_SelectedColor[3] = rgba.a;
		}

		glm::vec4 ColorPickerPanel::getSelectedColor() const
		{
			return glm::vec4(m_SelectedColor[0], m_SelectedColor[1], m_SelectedColor[2], m_SelectedColor[3]);
		}
	}
}