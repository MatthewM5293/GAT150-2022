#include "PhysicsComponent.h"
#include "Engine.h"

namespace neu 
{
	void PhysicsComponent::Update()
	{
		velocity += acceleration * neu::g_time.deltaTime;
		m_owner->m_transform.position += velocity * neu::g_time.deltaTime;
		velocity *= damping;

		acceleration = Vector2::zero;
	}

	bool PhysicsComponent::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool PhysicsComponent::Read(const rapidjson::Value& value)
	{
		return false;
	}

}
