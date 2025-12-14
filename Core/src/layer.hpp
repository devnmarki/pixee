#ifndef LAYER_HPP
#define LAYER_HPP

#include <memory>

#include "event/event.hpp"

namespace pixee
{
	namespace core
	{
		class Layer
		{
		public:
			virtual ~Layer() = default;

			virtual void onAttach() {}
			virtual void onUpdate() {}
			virtual void onRender() {}
			virtual void onEvent(event::Event& event) {}

			template<typename T, typename... Args>
			void transitionTo(Args&&... args)
			{
				queueTransition(std::move(std::make_unique<T>(std::forward<Args>(args)...)));
			}

		private:
			void queueTransition(std::unique_ptr<Layer> layer);
		};
	}
}

#endif