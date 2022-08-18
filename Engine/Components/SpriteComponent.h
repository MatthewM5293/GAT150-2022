#pragma once
#include "RenderComponent.h"
namespace neu
{
	class Texture;

	class SpriteComponent : public RenderComponent
	{
	public:
		// Inherited via RenderComponent
		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		// Inherited via RenderComponent
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

	public:
		std::shared_ptr<Texture> m_texture; //to model for modelComponent


	protected:


	

	};
}