#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <cassert>

#include "window.hpp"
#include "layer.hpp"
#include "utils.hpp"

namespace pixee
{
	namespace core
	{
		struct ApplicationSpecification
		{
			std::string name = "Pixee";
			WindowSpecification windowSpecs;
		};

		class Application
		{
		public:
			Application(const ApplicationSpecification& specs);
			~Application();
			
			static Application& getInstance();

			void run();
			void quit();

			template<typename T, typename... Args>
			void pushLayer(Args&&... args)
			{
				m_LayerStack.push_back(std::make_unique<T>(std::forward<Args>(args)...));
				m_LayerStack.back()->onAttach();
			}

			template<typename T>
			T* getLayer()
			{
				for (const auto& layer : m_LayerStack)
				{
					if (auto casted = dynamic_cast<T*>(layer.get()))
						return casted;
				}

				return nullptr;
			}

			std::shared_ptr<Window> getWindow() const;
			SDL_Renderer* getRenderer() const;

		private:
			ApplicationSpecification m_Specs;
			std::shared_ptr<Window> m_Window;
			bool m_IsRunning;

			std::vector<std::unique_ptr<Layer>> m_LayerStack;
		};
	}
}

#endif