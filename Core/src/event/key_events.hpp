#ifndef KEYEVENTS_HPP
#define KEYEVENTS_HPP

#include <format>

#include <SDL.h>

#include "event/event.hpp"

namespace pixee
{
	namespace event
	{
		class KeyEvent : public Event
		{
		public:
			inline SDL_Keycode getKeyCode() const { return m_KeyCode; }

		protected:
			KeyEvent(SDL_Keycode keyCode) : m_KeyCode(keyCode) { }

			SDL_Keycode m_KeyCode;
		};

		class KeyPressedEvent : public KeyEvent
		{
		public:
			KeyPressedEvent(SDL_Keycode keyCode) : KeyEvent(keyCode) { }

			std::string toString() const override
			{
				return std::format("KeyPressedEvent: {}", m_KeyCode);
			}

			EVENT_CLASS_TYPE(KeyPressed)
		};

		class KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(SDL_Keycode keyCode) : KeyEvent(keyCode) { }

			std::string toString() const override
			{
				return std::format("KeyReleasedEvent: {}", m_KeyCode);
			}

			EVENT_CLASS_TYPE(KeyReleased)
		};

		class KeyDownEvent : public KeyEvent
		{
		public:
			KeyDownEvent(SDL_Keycode keyCode) : KeyEvent(keyCode) { }

			std::string toString() const override
			{
				return std::format("KeyDownEvent: {}", m_KeyCode);
			}

			EVENT_CLASS_TYPE(KeyDown)
		};
	}
}

#endif