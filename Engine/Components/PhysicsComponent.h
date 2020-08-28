#pragma once

#include "Component.h"
#include "Math/Vector2.h"

namespace nc
{
	class PhysicsComponent : public Component
	{
		public:
			virtual bool Create(void* data = nullptr) override;
			virtual void Destroy() override;
			virtual Object* Clone() override { return new PhysicsComponent{ *this }; }

			virtual void Update() override;

			virtual void ApplyForce(const Vector2& force) { m_force = force; }
			virtual Vector2& GetVelocity() { return m_velocity; }
			void SetDrag(float drag) { m_drag = drag; }

		protected:
			Vector2 m_velocity;
			Vector2 m_force;
			float m_drag = 1;

	};
}