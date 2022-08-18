#pragma once
#include "GameObject.h"
#include "Math/Transform.h"
#include "Framework/Component.h"
#include <vector>
#include <memory>

namespace neu
{
	class Scene; //forward declartion
	class Renderer;
	class Actor : public GameObject, public ISerializable
	{
	public:
		Actor() = default;
		Actor(const Transform& transform) : m_transform{ transform } {}
		//Actor(Model model, Transform transform) : GameObject{ transform }, m_model{ model } {}

		virtual void Update() override;
		virtual void Draw(Renderer& renderer);

		// Inherited via ISerializable
		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void AddChild(std::unique_ptr<Actor> child);

		void AddComponent(std::unique_ptr<Component> component);
		template<typename T>
		T* GetComponent();

		virtual void OnCollision(Actor* other) {}
		float GetRadius() { return 0; }// m_model.GetRadius()* std::max(m_transform.scale.x, m_transform.scale.y); }
		
		const std::string& GetTag() { return tag; }
		void SetTag(const std::string& name) { this->name = name; }
		const std::string& GetName() { return tag; }
		void SetName(const std::string& name) { this->name = name; }

		friend class Scene;
		friend class Component;
		Transform m_transform;

	protected:
		std::string name;
		std::string tag;


		bool m_destroy = false;
		//physics
		Vector2 m_velocity;
		float m_damping = 1;

		Scene* m_scene = nullptr; //can make gets and sets
		Actor* m_parent = nullptr;

		std::vector<std::unique_ptr<Component>> m_components;
		std::vector<std::unique_ptr<Actor>> m_children;
	};

	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components)
		{
			T* result = dynamic_cast<T*>(component.get());
			if (result) return result;
		}

		return nullptr;
	}
}