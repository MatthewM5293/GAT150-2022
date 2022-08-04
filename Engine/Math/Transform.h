#pragma once
#include "Vector2.h"

namespace neu
{
	struct Transform
	{
		Vector2 position;
		float rotation;
		//float scale;
		Vector2 scale{ 1, 1 };
	};
}
