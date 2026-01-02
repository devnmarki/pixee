#ifndef OVERLAY_LAYER_HPP
#define OVERLAY_LAYER_HPP

#include "core.hpp"

#include "ui/modal/new_canvas_modal.hpp"

namespace pixee
{
	class OverlayLayer : public core::Layer
	{
	public:
		OverlayLayer();

		void onGuiRender() override;

		ui::NewCanvasModal& getNewCanvasModal() { return m_NewCanvasModal; }

	private:
		ui::NewCanvasModal m_NewCanvasModal;
	};
}

#endif