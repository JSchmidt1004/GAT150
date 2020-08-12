#pragma once

#include <vector>

#include "Object.h"
#include "Math/Transform.h"
#include "Engine.h"

namespace nc
{
	class Component;

	class GameObject : public Object
	{
		public:
			virtual bool Create(void* data = nullptr) override;
			virtual void Destroy() override;

			void Update();
			void Draw();

			void AddComponent(Component* component);
			void RemoveComponent(Component* component);
			void RemoveAllComponents();

			template<typename T>
			T* GetComponent();

			friend class Component;
			friend class PhysicsComponent;

		public:
			Transform m_transform;
			Engine* m_engine;

		protected:
			std::vector<Component*> m_components;
	};

	template<typename T>
	T* GameObject::GetComponent()
	{
		T* result = nullptr;
		for (auto component : m_components)
		{
			result = dynamic_cast<T*>(component);
			if (result) break;
		}

		return result;
	}
}