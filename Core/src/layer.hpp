#ifndef LAYER_HPP
#define LAYER_HPP

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
		};
	}
}

#endif