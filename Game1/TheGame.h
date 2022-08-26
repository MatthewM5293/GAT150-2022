#pragma once
#include "Framework/Game.h"

class TheGame : public neu::Game
{
public:
	// Inherited via Game
	virtual void Initialize() override;
	virtual void Shutdown() override;
	virtual void Update() override;
	virtual void Draw(neu::Renderer& renderer) override;
};