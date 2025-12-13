#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <memory>
#include <cassert>

#include "window.hpp"

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

			std::shared_ptr<Window> getWindow() const;
			SDL_Renderer* getRenderer() const;

		private:
			ApplicationSpecification m_Specs;
			std::shared_ptr<Window> m_Window;
			bool m_IsRunning;
		};
	}
}

#endif