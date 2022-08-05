#pragma once
#include "Framework/Component.h"

namespace neu
{
	class PlayerComponent : public Component
	{
	public:
		PlayerComponent() = default;

		void Update() override;
	};
}