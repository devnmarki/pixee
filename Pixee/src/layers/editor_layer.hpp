#ifndef EDITORLAYER_HPP
#define EDITORLAYER_HPP

#include "core.hpp"

namespace pixee
{
	class EditorLayer : public core::Layer
	{
	public:
		EditorLayer() = default;

		void onAttach() override;
		void onUpdate() override;
	};
}

#endif