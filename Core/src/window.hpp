#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>

#include <SDL.h>

#include "event/event.hpp"

namespace pixee
{
	namespace core
	{
		struct WindowSpecification
		{
			std::string title;
			int width;
			int height;
			bool isResizable = false;
			bool enableVSync = false;

			using EventCallback = std::function<void(event::Event&)>;
			EventCallback eventCallback;
		};

		class Window
		{
		public:
			Window(const WindowSpecification& specs);
			~Window();

			void create();

			void beginFrame() const;
			void endFrame() const;

			void raiseEvent(event::Event& event);

			SDL_Window* getHandle() const;
			SDL_Renderer* getRenderer() const;
			int getWidth() const;
			int getHeight() const;

		private:
			WindowSpecification m_Specs;

			SDL_Window* m_Handle;
			SDL_Renderer* m_Renderer;
		};
	}
}

#endif