#ifndef MODAL_HPP
#define MODAL_HPP

#include "core.hpp"

namespace pixee
{
	namespace ui
	{
		struct ModalSpecifications
		{
			int width = 100;
			int height = 100;
			std::string title = "Modal";
		};

		class Modal
		{
		public:
			Modal(const ModalSpecifications& specs = ModalSpecifications());

			void render();

			void show();
			void hide();

			virtual void onAccept() { }
			virtual void onCancel() { }

		protected:
			virtual void renderGui() { }

		private:
			ModalSpecifications m_Specs;

			bool m_Shown = false;
			bool m_JustShown = false;
		};
	}
}

#endif