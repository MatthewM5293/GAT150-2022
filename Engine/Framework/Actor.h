#pragma once
#include "GameObject.h"
//#include "../Renderer/Model.h"
#include "Framework/Component.h"
#include <vector>
#include <memory>

namespace neu
{
	class Scene; //forward declartion
	class Renderer;
	class Actor : public GameObject
	{
	public:
		Actor() = default;
		Actor(const Transform& transform) : m_transform{ transform } {}
		//Actor(Model model, Transform transform) : GameObject{ transform }, m_model{ model } {}

		virtual void Update() override;
		virtual void Draw(Renderer& renderer);

		void AddComponent(std::unique_ptr<Component> component);

		virtual void OnCollision(Actor* other) {}
		float GetRadius() { return 0; }// m_model.GetRadius()* std::max(m_transform.scale.x, m_transform.scale.y); }
		
		std::string& GetTag() { return m_tag; }

		friend class Scene;
		friend class Component;
		Transform m_transform;
	protected:
		std::string m_tag;
		bool m_destroy = false;
		//physics
		Vector2 m_velocity;
		float m_damping = 1;

		Scene* m_scene = nullptr; //can make gets and sets
		std::vector<std::unique_ptr<Component>> m_components;

	};
}