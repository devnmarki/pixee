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

		class MouseMovedEvent : public Event
		{
		public:
			MouseMovedEvent(double x, double y, double dx, double dy) : m_X(x), m_Y(y), m_DeltaX(dx), m_DeltaY(dy) { }

			double getX() const { return m_X; }
			double getY() const { return m_Y; }
			double getDeltaX() const { return m_DeltaX; }
			double getDeltaY() const { return m_DeltaY; }

			std::string toString() const override
			{
				return std::format("MouseMovedEvent: X: {}, Y: {}, DeltaX: {}, DeltaY: {}", m_X, m_Y, m_DeltaX, m_DeltaY);
			}

			EVENT_CLASS_TYPE(MouseMoved)

		private:
			double m_X;
			double m_Y;

			double m_DeltaX;
			double m_DeltaY;
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