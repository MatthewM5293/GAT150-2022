#pragma once
#include <string>

namespace neu 
{
	class Resource
	{
	public:
		virtual bool Create(std::string name, ...) = 0;
	};
}