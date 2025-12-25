#include "modal.hpp"

namespace pixee
{
	namespace ui
	{
		Modal::Modal(const ModalSpecifications& specs)
			: m_Specs(specs)
		{

		}

		void Modal::render()
		{
			if (!m_Shown)
				return;

			if (m_JustShown)
			{
				ImGui::OpenPopup(m_Specs.title.c_str());
				m_JustShown = false;
			}

			ImVec2 center = ImGui::GetMainViewport()->GetCenter();
			ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
			ImGui::SetNextWindowSize(ImVec2(m_Specs.width, m_Specs.height), ImGuiCond_Appearing);

			if (ImGui::BeginPopupModal(m_Specs.title.c_str(), nullptr, ImGuiWindowFlags_NoResize))
			{
				renderGui();

				ImGui::Separator();

				float buttonWidth = 80.0f;
				float spacing = ImGui::GetStyle().ItemSpacing.x;
				float availWidth = ImGui::GetContentRegionAvail().x;
				float offset = availWidth - (buttonWidth * 2 + spacing);

				ImGui::SetCursorPosX(offset);

				if (ImGui::Button("OK", ImVec2(buttonWidth, 0)))
				{
					onAccept();
					hide();
				}

				ImGui::SameLine();

				if (ImGui::Button("Cancel", ImVec2(buttonWidth, 0)))
				{
					onCancel();
					hide();
				}

				ImGui::EndPopup();
			}
		}

		void Modal::show()
		{
			m_Shown = true;
			m_JustShown = true;
		}

		void Modal::hide()
		{
			m_Shown = false;
			ImGui::CloseCurrentPopup();
		}
	}
}