#ifndef TOOLS_PANEL_HPP
#define TOOLS_PANEL_HPP

#include <vector>
#include <print>

#include "core.hpp"

namespace pixee
{
	class Canvas;
	class Tool;
	enum class ToolType;

	namespace ui
	{
		class ToolsPanel
		{
		public:
			ToolsPanel(Canvas& canvas);

			void render(std::shared_ptr<Tool> activeTool, std::function<void(std::shared_ptr<Tool>)> onToolSelcted);

			std::shared_ptr<Tool> getToolByType(ToolType type) const;

			using ToolList = std::vector<std::shared_ptr<Tool>>;
			ToolList& getAvailableTools() { return m_AvailableTools; }

		private:
			ToolList m_AvailableTools;
		};
	}
}

#endif