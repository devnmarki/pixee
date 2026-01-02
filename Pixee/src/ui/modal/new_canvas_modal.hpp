#ifndef NEW_CANVAS_MODAL_HPP
#define NEW_CANVAS_MODAL_HPP

#include "modal.hpp"

namespace pixee
{
	namespace ui
	{
		class NewCanvasModal : public Modal
		{
		public:
			NewCanvasModal();

			void renderGui() override;
			
			void onAccept() override;

		private:
			int m_DesiredWidth = 16;
			int m_DesiredHeight = 16;
		};
	}
}

#endif