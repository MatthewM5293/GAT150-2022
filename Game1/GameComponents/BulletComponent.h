#pragma once
#include "Components/CharacterComponent.h"

class BulletComponent : public neu::CharacterComponent
{
public:
	CLASS_DECLARATION(BulletComponent)



		// Inherited via CharacterComponent
		virtual void Update() override;

	virtual void OnCollisionEnter(neu::Actor* other) override;

	virtual void OnCollisionExit(neu::Actor* other) override;

	virtual void OnNotify(const neu::Event& event) override;

};
