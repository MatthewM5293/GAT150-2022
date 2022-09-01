#include "BulletComponent.h"
#include "Engine.h"
#include <iostream>

void BulletComponent::Update()
{
}

void BulletComponent::OnCollisionEnter(neu::Actor* other)
{
    if (other->GetTag() == "Enemy")
    {
        neu::Event event;
        event.name = "EVENT_DAMAGE";
        event.data = damage;
        event.receiver = other;

        neu::g_eventManager.Notify(event);
    }
}

void BulletComponent::OnCollisionExit(neu::Actor* other)
{
}

void BulletComponent::OnNotify(const neu::Event& event)
{
    if (event.name == "EVENT_DAMAGE")
    {
        health -= std::get<float>(event.data);
        if (health <= 0)
        {
            m_owner->SetDestroy();
        }
        if (event.name == "EVENT_HEAL")
        {
            health += std::get<float>(event.data);
        }
    }
}
