#include "new_canvas_modal.hpp"

#include "layers/editor_layer.hpp"

namespace pixee
{
	namespace ui
	{
		NewCanvasModal::NewCanvasModal()
			: Modal({ 300, 200, "Create New Canvas" })
		{

		}

		void NewCanvasModal::renderGui()
		{
			ImGui::InputInt("Canvas Width", &m_DesiredWidth);
			ImGui::InputInt("Canvas Height", &m_DesiredHeight);
		}

		void NewCanvasModal::onAccept()
		{
			core::Application::getInstance().getLayer<EditorLayer>()->getCanvas().reset(m_DesiredWidth, m_DesiredHeight);
		}
	}
}