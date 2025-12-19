#ifndef COLOR_PICKER_PANEL_HPP
#define COLOR_PICKER_PANEL_HPP

#include <vec4.hpp>

#include "core.hpp"

namespace pixee
{
	namespace ui
	{
		class ColorPickerPanel
		{
		public:
			ColorPickerPanel();

			void render();

			glm::vec4 getSelectedColor() const;
		
		public:
			inline static const std::string WINDOW_ID = "Color Picker";

		private:

			float m_SelectedColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
		};
	}
}

#endif