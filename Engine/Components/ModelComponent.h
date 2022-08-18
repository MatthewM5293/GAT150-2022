#pragma once
#include "RenderComponent.h"

namespace neu
{
	class Model;

	class ModelComponent : public RenderComponent
	{
	public:
		ModelComponent() = default;

	public:
		// Inherited via RenderComponent
		virtual void Update() override;
		virtual void Draw(Renderer& renderer) override;

		// Inherited via RenderComponent
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;
		//to model for modelComponent

	public:
		std::shared_ptr<Model> m_model;
		
	};
}
