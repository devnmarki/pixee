#ifndef MENU_BAR_HPP
#define MENU_BAR_HPP

#include <print>
#include <functional>

#include "core.hpp"

namespace pixee
{
	namespace ui
	{
		struct MenuBarContext
		{
			std::function<void()> onNew = []{};
			std::function<void()> onOpen = []{};
			std::function<void()> onSaveAs = []{};
			std::function<void()> onSave = []{};
			std::function<void()> onExportAsPNG = []{};
		};

		class MenuBar
		{
		public:
			MenuBar(const MenuBarContext& ctx = MenuBarContext());

			void render();

			void setContext(const MenuBarContext& ctx);

			MenuBarContext& getContext() { return m_Ctx; }

		private:
			MenuBarContext m_Ctx;
		};
	}
}

#endif