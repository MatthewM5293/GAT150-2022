#pragma once
#include "../Math/Transform.h"

namespace neu
{
	class GameObject
	{
	public:
		GameObject() = default;
		
		virtual void Update() = 0;

		//Transform& GetTransform() { return m_transform; }

	};
}


