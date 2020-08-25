#include "pch.h"
#include "PlayerComponent.h"
#include "Components/RigidBodyComponent.h"

bool nc::PlayerComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
	m_owner->GetComponent<PhysicsComponent>()->SetDrag(0.97);
    return false;
}

void nc::PlayerComponent::Destroy()
{
}

void nc::PlayerComponent::Update()
{
	nc::Vector2 force{ 0, 0 };
	
	//Player Controller
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = -200000;
		//m_owner->m_transform.angle -= 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
	}
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = 200000;
		//m_owner->m_transform.angle += 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
	}
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
	{
		force.y = -20000000;
	}

	/*if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_W) == nc::InputSystem::eButtonState::HELD)
	{
		force = nc::Vector2::forward * 1000.0f;
		
	}*/

	//force = nc::Vector2::Rotate(force, nc::DegreesToRadians(m_owner->m_transform.angle));

	RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
	if (component)
	{
		component->ApplyForce(force);
	}
}
