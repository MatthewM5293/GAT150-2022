#include "Actor.h"

namespace neu 
{
	void Actor::Draw(Renderer& renderer)
	{
		m_model.Draw(renderer, m_transform.position, m_transform.rotation, m_transform.scale);
	}
}
