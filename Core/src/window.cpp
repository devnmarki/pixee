#include "window.hpp"

namespace pixee
{
	namespace core
	{
		Window::Window(const WindowSpecification& specs)
			: m_Specs(specs), m_Handle(nullptr), m_Renderer(nullptr)
		{

		}

		Window::~Window()
		{
			if (m_Renderer) 
				SDL_DestroyRenderer(m_Renderer);
			
			if (m_Handle)
				SDL_DestroyWindow(m_Handle);
		}

		void Window::create()
		{
			m_Handle = SDL_CreateWindow(m_Specs.title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Specs.width, m_Specs.height, SDL_WINDOW_SHOWN);
			if (!m_Handle)
			{
				std::cout << "FATAL: Failed to create window handle! Error: " << SDL_GetError() << std::endl;
				return;
			}

			m_Renderer = SDL_CreateRenderer(m_Handle, -1, SDL_RENDERER_ACCELERATED);
			if (!m_Renderer)
			{
				std::cout << "FATAL: Failed to create renderer! Error: " << SDL_GetError() << std::endl;
				return;
			}
		}

		void Window::beginFrame() const
		{
			SDL_SetRenderDrawColor(m_Renderer, 20, 20, 20, 255);
			SDL_RenderClear(m_Renderer);
		}

		void Window::endFrame() const
		{
			SDL_RenderPresent(m_Renderer);
		}

		void Window::raiseEvent(event::Event& event)
		{
			if (m_Specs.eventCallback)
				m_Specs.eventCallback(event);
		}

		SDL_Window* Window::getHandle() const
		{
			return m_Handle;
		}

		SDL_Renderer* Window::getRenderer() const
		{
			return m_Renderer;
		}
	}
}