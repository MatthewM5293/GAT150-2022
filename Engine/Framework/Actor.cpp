#include "Actor.h"
#include "Components/RenderComponent.h"

namespace neu 
{
	void Actor::Update()
	{
		for (auto& component : m_components)
		{
			component->Update();
		}
	}

	void Actor::Draw(Renderer& renderer)
	{
		for (auto& component : m_components)
		{
			auto renderComponent = dynamic_cast<RenderComponent*>(component.get());
			if (renderComponent)
			{
				renderComponent->Draw(renderer);
			}
			//component->Update();
		}
	}
	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->m_owner = this;
		m_components.push_back(std::move(component));
	}
}
