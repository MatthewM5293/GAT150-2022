#include "EventManager.h"

namespace neu
{
	void EventManager::Initialize()
	{
	}

	void EventManager::Shutdown()
	{
	}

	void EventManager::Update()
	{
	}

	void EventManager::Subscribe(const std::string& name, Event::functionPtr function, GameObject* receiver)
	{
		Observer observer;
		observer.receiver = receiver;
		observer.function = function;

		m_events[name].push_back(observer);
	}

	void EventManager::Unsubscribe(const std::string& name, GameObject* receiver)
	{
		// get list of observers for event
		auto& observers = m_events[name];

		// remove observer with matching receiver from observers
		for (auto iter = observers.begin(); iter != observers.end(); iter++)
		{
			if (iter->receiver == receiver)
			{
				observers.erase(iter);
				break;
			}
		}
	}

	void EventManager::Notify(const Event& event)
	{
		auto& observers = m_events[event.name];
		for (auto& observer : observers)
		{
			if (event.receiver == nullptr || event.receiver == observer.receiver)
			observer.function(event);
		}
	}
}