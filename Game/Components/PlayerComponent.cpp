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

	auto contacts = m_owner->GetContactsWithTag("Floor");
	bool onGround = !contacts.empty();
	
	//Player Controller
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_A) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = -80;
		//m_owner->m_transform.angle -= 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
	}
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = 80;
		//m_owner->m_transform.angle += 200.0f * m_owner->m_engine->GetTimer().DeltaTime();
	}
	if (onGround && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
	{
		force.y = -1200;
	}

	//

	RigidBodyComponent* component = m_owner->GetComponent<RigidBodyComponent>();
	if (component)
	{
		component->ApplyForce(force);
	}

	auto coinContacts = m_owner->GetContactsWithTag("Coin");
	for (GameObject* contact : coinContacts)
	{
		contact->m_flags[GameObject::eFlags::DESTROY] = true;
		//Play sound
	}
}
