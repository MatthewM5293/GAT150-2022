#pragma once
#include "Actor.h"
#include "Factory.h"

#include <list>
#include <memory>

namespace neu 
{
	//forward declarations
	//class Actor;
	class Renderer;
	class Game;

	class Scene : public GameObject, public ISerializable
	{
	public:
		Scene() = default;
		Scene(Game* game) : m_game{ game } {}
		Scene(const Scene& other) {}
		~Scene() = default;

		CLASS_DECLARATION(Scene)

		void Initialize() override;
		void Update() override;
		void Draw(Renderer& renderer);

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Add(std::unique_ptr<Actor> actor);
		void RemoveAll();

		template<typename T>
		T* GetActor();

		template<typename T = Actor>
		T* GetActorFromName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsFromTag(const std::string& tag);

		Game* GetGame() { return m_game; }

	private:
		Game* m_game;
		std::list<std::unique_ptr<Actor>> m_actors;

	};


	template<typename T>
	inline T* Scene::GetActor()
	{
		for (auto& actor : m_actors)
		{
			T* result = dynamic_cast<T*>(actor.get());
			if (result) return result;
		}

		return nullptr;
	}

}
	template<typename T>
	inline T* neu::Scene::GetActorFromName(const std::string& name)
	{
		//  !! for loop (range based) through m_actors 
		for (auto& actors : m_actors)
		{
			{
				if (name == actors->GetName())
					{
						return dynamic_cast<T*>(actors.get()); //  !! get() actor pointer); 
					}
			}
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> neu::Scene::GetActorsFromTag(const std::string& tag)
	{
		std::vector<T*> result;

		//  !! for loop (range based) through m_actors 
		for (auto& actors : m_actors)
		{
			{
				if (actors.get()->GetName()) //  !! compare name to actor GetName()) 
					{
						T* tagActor = dynamic_cast<T*>(actors.get()); //  !! get() actor pointer); 
						if (tagActor) //  !! push back tagActor to result vector 
						{
							result.push_back(tagActor);
						}
					}
			}
		}
		return result;
	}