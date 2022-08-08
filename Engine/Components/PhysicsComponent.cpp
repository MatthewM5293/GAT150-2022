#include "PhysicsComponent.h"
#include "Engine.h"

namespace neu 
{
	void PhysicsComponent::Update()
	{
		m_velocity += m_acceleration * neu::g_time.deltaTime;
		m_owner->m_transform.position += m_velocity * neu::g_time.deltaTime;
		m_velocity *= m_damping;

		m_acceleration = Vector2::zero;
	}

}
