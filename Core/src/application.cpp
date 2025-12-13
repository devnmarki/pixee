#include "application.hpp"

namespace pixee
{
	namespace core
	{
		static Application* s_Instance = nullptr;

		Application::Application(const ApplicationSpecification& specs)
			: m_Specs(specs), m_IsRunning(true)
		{
			s_Instance = this;

			if (m_Specs.windowSpecs.title.empty())
				m_Specs.windowSpecs.title = m_Specs.name;

			m_Window = std::make_shared<Window>(m_Specs.windowSpecs);
			m_Window->create();
		}

		Application::~Application()
		{
			SDL_Quit();

			s_Instance = nullptr;
		}

		Application& Application::getInstance()
		{
			assert(s_Instance);
			return *s_Instance;
		}

		void Application::run()
		{
			while (m_IsRunning)
			{
				SDL_Event event;
				if (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
					case SDL_QUIT:
						quit();
						break;
					case SDL_KEYDOWN:
						if (event.key.keysym.sym = SDLK_ESCAPE)
							quit();
						break;
					}
				}

				for (const auto& layer : m_LayerStack)
					layer->onUpdate();

				m_Window->beginFrame();
				
				for (const auto& layer : m_LayerStack)
					layer->onRender();

				m_Window->endFrame();
			}
		}

		void Application::quit()
		{
			m_IsRunning = false;
		}

		std::shared_ptr<Window> Application::getWindow() const
		{
			return m_Window;
		}

		SDL_Renderer* Application::getRenderer() const
		{
			return m_Window->getRenderer();
		}
	}
}