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
			std::function<void()> onNewRequest = []{};
			std::function<void()> onOpenRequest = []{};
			std::function<void()> onSaveAsRequest = []{};
			std::function<void()> onSaveRequest = []{};

			std::function<void()> onShowGridRequest = []{};
			std::function<void()> onResizeRequest = []{};
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