#include "pch.h"
#include "PlayerComponent.h"
#include "Core/EventManager.h"
#include "Components/RigidBodyComponent.h"
#include "Components/AudioComponent.h"
#include "Components/SpriteComponent.h"

bool nc::PlayerComponent::Create(void* data)
{
	m_owner = static_cast<GameObject*>(data);
	m_owner->GetComponent<PhysicsComponent>()->SetDrag(0.97);

	EventManager::Instance().Subscribe("CollisionEnter", std::bind(&PlayerComponent::OnCollisionEnter, this, std::placeholders::_1), m_owner);
	EventManager::Instance().Subscribe("CollisionExit", std::bind(&PlayerComponent::OnCollisionExit, this, std::placeholders::_1), m_owner);

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
	}
	if (m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_D) == nc::InputSystem::eButtonState::HELD)
	{
		force.x = 80;
	}
	if (onGround && m_owner->m_engine->GetSystem<nc::InputSystem>()->GetButtonState(SDL_SCANCODE_SPACE) == nc::InputSystem::eButtonState::PRESSED)
	{
		force.y = -1200;

		AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
		audioComponent->SetSoundName("jump.wav");
		audioComponent->Play();
	}

	PhysicsComponent* component = m_owner->GetComponent<PhysicsComponent>();
	if (component)
	{
		component->ApplyForce(force);

		Vector2 velocity = component->GetVelocity();

		SpriteComponent* spriteComponent = m_owner->GetComponent<SpriteComponent>();
		if (velocity.x <= -0.5f) spriteComponent->Flip();
		if (velocity.x >= 0.5f) spriteComponent->Flip(false);
	}
}

	void nc::PlayerComponent::OnCollisionEnter(const Event & event)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

		if (gameObject->m_tag == "Enemy")
		{
			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			audioComponent->SetSoundName("grunt.wav");
			audioComponent->Play();
		}
		if (gameObject->m_tag == "Coin")
		{
			gameObject->m_flags[GameObject::eFlags::DESTROY] = true;

			AudioComponent* audioComponent = m_owner->GetComponent<AudioComponent>();
			audioComponent->SetSoundName("coin.wav");
			audioComponent->Play();
		}

		//std::cout << "collision enter: " << gameObject->m_name << std::endl;
	}

	void nc::PlayerComponent::OnCollisionExit(const Event& event)
	{
		GameObject* gameObject = dynamic_cast<GameObject*>(event.sender);

		//std::cout << "collision exit: " << gameObject->m_name << std::endl;
	}
