#pragma once
#include "Framework/Component.h"
#include "Physics/Collision.h"
#include "Physics/PhysicsSystem.H"

namespace neu
{
	class CollisionComponent : public Component, public ICollision
	{
	public:
		virtual void Initialize() override;
		virtual void Update() override;

		// Inherited via ICollision
		virtual void OnCollisionEnter(Actor* other) override;
		virtual void OnCollisionExit(Actor* other) override;

		// Inherited via Component
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	private:
		PhysicsSystem::CollisionData data;
	};
}