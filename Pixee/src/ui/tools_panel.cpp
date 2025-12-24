#include "tools_panel.hpp"

#include "tool/tools.hpp"

namespace pixee
{
	namespace ui
	{
		ToolsPanel::ToolsPanel(Canvas& canvas)
		{
			m_AvailableTools.push_back(std::make_shared<PenTool>(canvas));
			m_AvailableTools.push_back(std::make_shared<EraserTool>(canvas));
			m_AvailableTools.push_back(std::make_shared<ColorPickerTool>(canvas));
			m_AvailableTools.push_back(std::make_shared<RectTool>(canvas));
			m_AvailableTools.push_back(std::make_shared<BucketFillTool>(canvas));
		}

		void ToolsPanel::render(std::shared_ptr<Tool> activeTool, std::function<void(std::shared_ptr<Tool>)> onToolSelcted)
		{
			ImGui::Begin("Tools");

			for (size_t i = 0; i < m_AvailableTools.size(); i++)
			{
				auto& availableTool = m_AvailableTools[i];

				bool selected = (availableTool == activeTool);
				if (selected)
					ImGui::PushStyleColor(ImGuiCol_Button, { 0.4f, 0.6f, 1.0f, 1.0f });
				
				ImGui::PushTextWrapPos(ImGui::GetCursorPosX() + 50.0f);
				if (ImGui::Button(availableTool->getName().c_str(), ImVec2(50.0f, 40.0f)))
				{
					onToolSelcted(availableTool);
				}
				ImGui::PopTextWrapPos();

				if (selected)
					ImGui::PopStyleColor();

				if (i < m_AvailableTools.size() - 1)
					ImGui::SameLine();
			}

			ImGui::End();
		}

		std::shared_ptr<Tool> ToolsPanel::getToolByType(ToolType type) const
		{
			for (const auto& tool : m_AvailableTools)
			{
				if (tool->getToolType() == type)
					return tool;
			}

			return nullptr;
		}
	}
}