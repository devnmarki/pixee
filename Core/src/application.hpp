#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
#include <ranges>
#include <unordered_set>
#include <print>

#include <imgui.h>
#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>

#include "window.hpp"
#include "layer.hpp"
#include "time.hpp"
#include "event/key_events.hpp"
#include "event/mouse_events.hpp"

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

			void raiseEvent(event::Event& event);

			using LayerStack = std::vector<std::unique_ptr<Layer>>;

			std::shared_ptr<Window> getWindow() const;
			SDL_Renderer* getRenderer() const;
			LayerStack& getLayerStack();

		private:
			void handleEvents(SDL_Event& e, std::unordered_set<SDL_Keycode>& heldKeys, std::unordered_set<event::MouseButton>& heldButtons);
			
			void handleKeyPressedEvent(const SDL_Event& e, std::unordered_set<SDL_Keycode>& heldKeys);
			void handleKeyReleasedEvent(const SDL_Event& e, std::unordered_set<SDL_Keycode>& heldKeys);
			void handleKeyDownEvent(const SDL_Event& e, std::unordered_set<SDL_Keycode>& heldKeys);
			
			void handleButtonPressedEvent(const SDL_Event& e, std::unordered_set<event::MouseButton>& heldButtons);
			void handleButtonReleasedEvent(const SDL_Event& e, std::unordered_set<event::MouseButton>& heldButtons);
			void handleButtonDownEvent(const SDL_Event& e, std::unordered_set<event::MouseButton>& heldButtons);
			void handleMouseMovedEvent(const SDL_Event& e);
			void handleMouseScrolledEvent(const SDL_Event& e);

		private:
			ApplicationSpecification m_Specs;
			std::shared_ptr<Window> m_Window;
			bool m_IsRunning;

			LayerStack m_LayerStack;
		};
	}
}

#endif