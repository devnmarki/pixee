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

			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

			ImGui::StyleColorsDark();

			ImGui_ImplSDL2_InitForSDLRenderer(m_Window->getHandle(), m_Window->getRenderer());
			ImGui_ImplSDLRenderer2_Init(m_Window->getRenderer());
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
			std::unordered_set<event::MouseButton> heldButtons;

			SDL_Event event;

			while (m_IsRunning)
			{
				frameStart = SDL_GetTicks();

				uint32_t currentTime = SDL_GetTicks();
				deltaTime = (currentTime - frameStart) / 1000.0f;
				lastTime = currentTime;

				if (deltaTime > 0.1f)
					deltaTime = 0.1f;

				utils::Time::deltaTime = deltaTime;

				if (SDL_PollEvent(&event))
				{
					ImGui_ImplSDL2_ProcessEvent(&event);

					handleEvents(event, heldKeys, heldButtons);
				}

				handleKeyDownEvent(event, heldKeys);
				handleButtonDownEvent(event, heldButtons);

				for (const auto& layer : m_LayerStack)
					layer->onUpdate();

				ImGui_ImplSDLRenderer2_NewFrame();
				ImGui_ImplSDL2_NewFrame();
				ImGui::NewFrame();

				static bool opt_fullscreen = true;
				static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;

				ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoBackground;
				if (opt_fullscreen) {
					const ImGuiViewport* viewport = ImGui::GetMainViewport();
					ImGui::SetNextWindowPos(viewport->WorkPos);
					ImGui::SetNextWindowSize(viewport->WorkSize);
					ImGui::SetNextWindowViewport(viewport->ID);
					window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
					window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
				}

				ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0, 0, 0, 0));
				ImGui::Begin("MyDockSpace", nullptr, window_flags);
				ImGui::PopStyleColor();

				ImGuiIO& io = ImGui::GetIO();
				if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {
					ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
					ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
				}
				ImGui::End();

				m_Window->beginFrame();

				for (const auto& layer : m_LayerStack)
					layer->onGuiRender();

				ImGui::Render();

				for (const auto& layer : m_LayerStack)
					layer->onRender();
				
				ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData(), m_Window->getRenderer());
				
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

		void Application::handleEvents(SDL_Event& e, std::unordered_set<SDL_Keycode>& heldKeys, std::unordered_set<event::MouseButton>& heldButtons)
		{
			switch (e.type)
			{
			case SDL_QUIT:
				quit();
				break;
			case SDL_KEYDOWN:
				if (e.key.keysym.sym == SDLK_ESCAPE)
					quit();
				handleKeyPressedEvent(e, heldKeys);
				break;
			case SDL_KEYUP:
				handleKeyReleasedEvent(e, heldKeys);
				break;
			case SDL_MOUSEBUTTONDOWN:
				handleButtonPressedEvent(e, heldButtons);
				break;
			case SDL_MOUSEBUTTONUP:
				handleButtonReleasedEvent(e, heldButtons);
				break;
			case SDL_MOUSEMOTION:
				handleMouseMovedEvent(e);
				break;
			case SDL_MOUSEWHEEL:
				handleMouseScrolledEvent(e);
				break;
			}
		}

		void Application::handleKeyPressedEvent(const SDL_Event& e, std::unordered_set<SDL_Keycode>& heldKeys)
		{
			SDL_Keycode key = e.key.keysym.sym;
			bool repeat = e.key.repeat;

			if (!repeat)
			{
				heldKeys.insert(key);
				event::KeyPressedEvent keyPressed(key);
				m_Window->raiseEvent(keyPressed);
			}
		}

		void Application::handleKeyReleasedEvent(const SDL_Event& e, std::unordered_set<SDL_Keycode>& heldKeys)
		{
			SDL_Keycode key = e.key.keysym.sym;
			heldKeys.erase(key);

			event::KeyReleasedEvent keyReleased(key);
			m_Window->raiseEvent(keyReleased);
		}

		void Application::handleKeyDownEvent(const SDL_Event& e, std::unordered_set<SDL_Keycode>& heldKeys)
		{
			for (auto& key : heldKeys)
			{
				event::KeyDownEvent keyDown(key);
				m_Window->raiseEvent(keyDown);
			}
		}

		void Application::handleButtonPressedEvent(const SDL_Event& e, std::unordered_set<event::MouseButton>& heldButtons)
		{
			event::MouseButton button = static_cast<event::MouseButton>(e.button.button);
			heldButtons.insert(button);

			event::MouseButtonPressedEvent mouseButtonPressed(button);
			m_Window->raiseEvent(mouseButtonPressed);
		}

		void Application::handleButtonReleasedEvent(const SDL_Event& e, std::unordered_set<event::MouseButton>& heldButtons)
		{
			event::MouseButton button = static_cast<event::MouseButton>(e.button.button);
			heldButtons.erase(button);

			event::MouseButtonReleasedEvent mouseReleasedEvent(button);
			m_Window->raiseEvent(mouseReleasedEvent);
		}

		void Application::handleButtonDownEvent(const SDL_Event& e, std::unordered_set<event::MouseButton>& heldButtons)
		{
			for (auto& button : heldButtons)
			{
				event::MouseButtonDownEvent mouseButtonDown(button);
				m_Window->raiseEvent(mouseButtonDown);
			}
		}

		void Application::handleMouseMovedEvent(const SDL_Event& e)
		{
			double mx = static_cast<double>(e.motion.x);
			double my = static_cast<double>(e.motion.y);
			double mdx = static_cast<double>(e.motion.xrel);
			double mdy = static_cast<double>(e.motion.yrel);

			event::MouseMovedEvent mouseMoved(mx, my, mdx, mdy);
			m_Window->raiseEvent(mouseMoved);
		}

		void Application::handleMouseScrolledEvent(const SDL_Event& e)
		{
			int32_t x = e.wheel.x;
			int32_t y = e.wheel.y;
			uint32_t direction = e.wheel.direction;

			event::MouseScrolledEvent mouseScrolled(x, y, direction);
			m_Window->raiseEvent(mouseScrolled);
		}
	}
}