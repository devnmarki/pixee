#include "editor_layer.hpp"
#include "editor_layer.hpp"

namespace pixee
{
	void EditorLayer::onAttach()
	{
		std::cout << "EditorLayer attached!" << std::endl;
	}

	void EditorLayer::onUpdate()
	{
		std::cout << "EditorLayer updating...\n";
	}
}