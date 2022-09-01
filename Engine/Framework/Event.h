#pragma once
#include "Math/Vector2.h"
#include <string>
#include <variant>
#include <functional>


namespace neu
{
	class GameObject;
	class Event
	{
	public:
		using functionPtr = std::function<void(const Event&)>;
	public:
		std::string name;
		GameObject* receiver = nullptr;
		std::variant<int, bool, float, std::string, void*, Vector2> data;
	};

	class INotify
	{
	public:
		virtual void OnNotify(const Event& event) = 0;
	};
}