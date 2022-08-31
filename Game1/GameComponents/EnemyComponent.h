#pragma once
#include "Components/CharacterComponent.h"

class EnemyComponent : public neu::CharacterComponent
{
public:
	CLASS_DECLARATION(EnemyComponent)

		virtual void Initialize() override;
	virtual void Update() override;

	virtual void OnCollisionEnter(neu::Actor* other) override;
	virtual void OnCollisionExit(neu::Actor* other) override;

	virtual void OnNotify(const neu::Event& event) override;

	virtual bool Write(const rapidjson::Value& value) const override;
	virtual bool Read(const rapidjson::Value& value) override;

protected:
};