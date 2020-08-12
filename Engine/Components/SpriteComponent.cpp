#include "pch.h"
#include "SpriteComponent.h"
#include "Graphics/Texture.h"

namespace nc
{
    bool nc::SpriteComponent::Create(void* data)
    {
        m_texture = m_owner->m_engine->GetSystem<nc::ResourceManager>()->Get<nc::Texture>("cars.png", m_owner->m_engine->GetSystem<nc::Renderer>());
        return true;
    }

    void nc::SpriteComponent::Destroy()
    {

    }

    void nc::SpriteComponent::Update()
    {

    }

    void nc::SpriteComponent::Draw()
    {
        //nc::Vector2 scale{ 1.0f, 1.0f }; 
        //scale *= m_owner->m_transform.scale;
        m_texture->Draw({ 128, 120, 48, 98 }, m_owner->m_transform.position, { 1.0f, 1.0f }, m_owner->m_transform.angle);
    }
}