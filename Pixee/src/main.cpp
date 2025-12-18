#include <iostream>

#include "layers/layers.hpp"

int main(int argc, char* argv[])
{
	pixee::core::ApplicationSpecification appSpecs;
	appSpecs.name = "Pixee";
	appSpecs.windowSpecs.width = 1280;
	appSpecs.windowSpecs.height = 720;

	pixee::core::Application app(appSpecs);
	app.pushLayer<pixee::EditorLayer>();
	app.pushLayer<pixee::UILayer>();
	app.run();

	return 0;
}