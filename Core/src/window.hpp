#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <iostream>

#include <SDL.h>

namespace pixee
{
	namespace core
	{
		struct WindowSpecification
		{
			std::string title;
			int width;
			int height;
		};

		class Window
		{
		public:
			Window(const WindowSpecification& specs);
			~Window();

			void create();

			SDL_Window* getHandle() const;
			SDL_Renderer* getRenderer() const;

		private:
			WindowSpecification m_Specs;

			SDL_Window* m_Handle;
			SDL_Renderer* m_Renderer;
		};
	}
}

#endif