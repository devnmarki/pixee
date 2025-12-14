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

			m_Specs.windowSpecs.eventCallback = [this](event::Event& event) { raiseEvent(event); };

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
			const int TARGET_FPS = 60;
			const int FRAME_DELAY = 1000 / TARGET_FPS;

			uint32_t frameStart;
			int frameTime;

			uint32_t lastTime = SDL_GetTicks();
			float deltaTime = 0.0f;

			std::unordered_set<SDL_Keycode> heldKeys;

			while (m_IsRunning)
			{
				frameStart = SDL_GetTicks();

				uint32_t currentTime = SDL_GetTicks();
				deltaTime = (currentTime - frameStart) / 1000.0f;
				lastTime = currentTime;

				if (deltaTime > 0.1f)
					deltaTime = 0.1f;

				utils::Time::deltaTime = deltaTime;

				SDL_Event event;
				if (SDL_PollEvent(&event))
				{
					switch (event.type)
					{
					case SDL_QUIT:
						quit();
						break;
					
					case SDL_KEYDOWN:
					{
						SDL_Keycode key = event.key.keysym.sym;
						bool repeat = event.key.repeat;

						if (!repeat)
						{
							heldKeys.insert(key);
							event::KeyPressedEvent keyPressed(key);
							m_Window->raiseEvent(keyPressed);
						}

						if (key == SDLK_ESCAPE)
							quit();
						break;
					}
					
					case SDL_KEYUP:
					{
						SDL_Keycode key = event.key.keysym.sym;
						heldKeys.erase(key);

						event::KeyReleasedEvent keyReleased(key);
						m_Window->raiseEvent(keyReleased);

						break;
					}
					}
				}

				for (auto& key : heldKeys)
				{
					event::KeyDownEvent keyDown(key);
					m_Window->raiseEvent(keyDown);
				}

				for (const auto& layer : m_LayerStack)
					layer->onUpdate();

				m_Window->beginFrame();
				
				for (const auto& layer : m_LayerStack)
					layer->onRender();

				m_Window->endFrame();

				frameTime = SDL_GetTicks() - frameStart;
				if (frameTime < FRAME_DELAY)
					SDL_Delay(FRAME_DELAY - frameTime);
			}
		}

		void Application::quit()
		{
			m_IsRunning = false;
		}

		void Application::raiseEvent(event::Event& event)
		{
			for (auto& layer : std::views::reverse(m_LayerStack))
			{
				layer->onEvent(event);
				if (event.handled)
					break;
			}
		}

		std::shared_ptr<Window> Application::getWindow() const
		{
			return m_Window;
		}

		SDL_Renderer* Application::getRenderer() const
		{
			return m_Window->getRenderer();
		}

		std::vector<std::unique_ptr<Layer>>& Application::getLayerStack()
		{
			return m_LayerStack;
		}
	}
}