#include "menu_bar.hpp"

namespace pixee
{
	namespace ui
	{
		MenuBar::MenuBar(const MenuBarContext& ctx)
			: m_Ctx(ctx)
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
						m_Ctx.onNew();
					}
					if (ImGui::MenuItem("Open", "Ctrl+O"))
					{
						m_Ctx.onOpen();
					}
					if (ImGui::MenuItem("Save as", "Ctrl+Alt+S"))
					{
						m_Ctx.onSaveAs();
					}
					if (ImGui::MenuItem("Save", "Ctrl+S"))
					{
						m_Ctx.onSave();
					}
					if (ImGui::MenuItem("Export as PNG", "Ctrl+E"))
					{
						m_Ctx.onExportAsPNG();
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
					if (ImGui::MenuItem("Show Grid", "Ctrl+G"))
					{
						std::println("Grid shown!");
					}
					if (ImGui::MenuItem("Reize", "Ctrl+R"))
					{
						std::println("Resizing canvas!");
					}
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}
		}

		void MenuBar::setContext(const MenuBarContext& ctx)
		{
			m_Ctx = ctx;
		}
	}
}