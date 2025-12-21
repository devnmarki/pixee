#ifndef COLOR_PICKER_TOOL_HPP
#define COLOR_PICKER_TOOL_HPP

#include <print>

#include "tool/tool.hpp"
#include "layers/ui_layer.hpp"

namespace pixee
{
	class ColorPickerTool : public Tool
	{
	public:
		ColorPickerTool(Canvas& canvas);
		
		void update() override;

		bool onMouseButtonDown(event::MouseButtonDownEvent& e) override;
	};
}

#endif