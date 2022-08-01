#pragma once
#include "GameObject.h"
#include "../Renderer/Model.h"

namespace neu
{
	class Scene; //forward declartion
	class Actor : public GameObject
	{
	public:
		Actor() = default;
		Actor(Model model, Transform transform) : GameObject{ transform }, m_model{ model } {}

		virtual void Update() override {}
		virtual void Draw(Renderer& renderer);

		virtual void OnCollision(Actor* other) {}
		float GetRadius() { return m_model.GetRadius() * m_transform.scale; }
		std::string& GetTag() { return m_tag; }

		friend class Scene;
	protected:
		std::string m_tag;
		bool m_destroy = false;
		//physics
		Vector2 m_velocity;
		float m_damping = 1;

		Scene* m_scene = nullptr; //can make gets and sets
		Model m_model;

	};
}