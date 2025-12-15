#ifndef MOUSEEVENTS_HPP
#define MOUSEEVENTS_HPP

#include <format>

#include <SDL.h>

#include "event/event.hpp"

namespace pixee
{
	namespace event
	{
		enum class MouseButton : uint8_t
		{
			Left = SDL_BUTTON_LEFT,
			Middle = SDL_BUTTON_MIDDLE,
			Right = SDL_BUTTON_RIGHT,
			X1 = SDL_BUTTON_X1,
			X2 = SDL_BUTTON_X2
		};

		class MouseButtonEvent : public Event
		{
		public:
			MouseButton getButton() const { return m_Button; }

		protected:
			MouseButtonEvent(MouseButton button) : m_Button(button) { }

		protected:
			MouseButton m_Button;
		};

		class MouseButtonPressedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonPressedEvent(MouseButton button) : MouseButtonEvent(button) { }

			std::string toString() const override
			{
				return std::format("MouseButtonPressedEvent: {}", static_cast<uint8_t>(m_Button));
			}

			EVENT_CLASS_TYPE(MouseButtonPressed)
		};

		class MouseButtonReleasedEvent : public MouseButtonEvent
		{
		public:
			MouseButtonReleasedEvent(MouseButton button) : MouseButtonEvent(button) { }

			std::string toString() const override
			{
				return std::format("MouseButtonReleasedEvent: {}", static_cast<uint8_t>(m_Button));
			}

			EVENT_CLASS_TYPE(MouseButtonReleased)
		};

		class MouseButtonDownEvent : public MouseButtonEvent
		{
		public:
			MouseButtonDownEvent(MouseButton button) : MouseButtonEvent(button) { }

			std::string toString() const override
			{
				return std::format("MouseButtonDownEvent: {}", static_cast<uint8_t>(m_Button));
			}

			EVENT_CLASS_TYPE(MouseButtonDown)
		};
	}
}

#endif