#ifndef EVENT_HPP
#define EVENT_HPP

#include <string>
#include <functional>

namespace pixee
{
	namespace event
	{
		enum class EventType {
			None = 0,
			KeyPressed, KeyReleased, KeyDown,
			ButtonPressed, ButtonReleased
		};

#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::type; }\
								virtual EventType getEventType() const override { return getStaticType(); }\
								virtual const char* getName() const override { return #type; }

		class Event
		{
		public:
			virtual ~Event() = default;
		
			virtual EventType getEventType() const = 0;
			virtual const char* getName() const = 0;
			virtual std::string toString() const { return getName(); }

		public:
			bool handled = false;
		};

		class EventDispatcher
		{
			template<typename T>
			using EventCallback = std::function<bool(T&)>;

		public:
			EventDispatcher(Event& event) : m_Event(event) { }

			template<typename T>
			bool dispatch(EventCallback<T> callback)
			{
				if (m_Event.getEventType() == T::getStaticType() && !m_Event.handled)
				{
					m_Event.handled = callback(*(T*)&m_Event);
					return true;
				}
				return false;
			}

		private:
			Event& m_Event;
		};
	}
}

#endif