#ifndef EDITORLAYER_HPP
#define EDITORLAYER_HPP

#include <print>

#include "core.hpp"

namespace pixee
{
	class EditorLayer : public core::Layer
	{
	public:
		EditorLayer() = default;

		void onAttach() override;
		void onUpdate() override;
		void onEvent(event::Event& event) override;

	private:
		bool onKeyPressedEvent(event::KeyPressedEvent& e);
	};
}

#endif