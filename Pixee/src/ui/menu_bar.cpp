#include "menu_bar.hpp"

namespace pixee
{
	namespace ui
	{
		MenuBar::MenuBar()
		{

		}

		void MenuBar::render()
		{
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					if (ImGui::MenuItem("New", "Ctrl+N"))
					{
						std::println("Creating new canvas!");
					}
					if (ImGui::MenuItem("Save as", "Ctrl+Alt+S"))
					{
						std::println("Saving canvas first time!");
					}
					if (ImGui::MenuItem("Save", "Ctrl+S"))
					{
						std::println("Saving canvas again!");
					}
					if (ImGui::MenuItem("Export as PNG", "Ctrl+E"))
					{
						std::println("Exporting canvas as PNG!");
					}
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Edit"))
				{
					if (ImGui::MenuItem("Undo", "Ctrl+Z"))
					{
						std::println("Undo!");
					}
					if (ImGui::MenuItem("Redo", "Ctrl+Shift+Z"))
					{
						std::println("Redo!");
					}
					ImGui::EndMenu();
				}

				if (ImGui::BeginMenu("Canvas"))
				{
					if (ImGui::MenuItem("Reize", "Ctrl+R"))
					{
						std::println("Resizing canvas!");
					}
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}
		}
	}
}