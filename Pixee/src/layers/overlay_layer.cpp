#include "overlay_layer.hpp"

namespace pixee
{
	OverlayLayer::OverlayLayer()
		: m_NewCanvasModal()
	{

	}

	void OverlayLayer::onGuiRender()
	{
		m_NewCanvasModal.render();
	}
}