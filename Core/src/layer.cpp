#include "layer.hpp"

#include "application.hpp"

namespace pixee
{
	namespace core
	{
		void Layer::queueTransition(std::unique_ptr<Layer> toLayer)
		{
			auto& layerStack = Application::getInstance().getLayerStack();
			for (auto& layer : layerStack)
			{
				if (layer.get() == this)
				{
					layer = std::move(toLayer);
					return;
				}
			}
		}
	}
}