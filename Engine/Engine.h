#pragma once

#include <vector>
#include "Core/Timer.h"
#include "Input/InputSystem.h"
#include "Physics/PhysicsSystem.h"
#include "Resources/ResourceManager.h"
#include "Graphics/Renderer.h"
#include "Audio/AudioSystem.h"

namespace nc
{
	class System;

	class Engine
	{
		public:
			bool Startup();
			void Shutdown();

			void Update();

			nc::FrameTimer& GetTimer() { return m_timer; }

			template<typename T>
			T* GetSystem();

		protected:
			std::vector<System*> m_systems;
			nc::FrameTimer m_timer;
	};

	template<typename T>
	T* Engine::GetSystem()
	{
		T* result = nullptr;
		for (auto system : m_systems)
		{
			result = dynamic_cast<T*>(system);
			if (result) break;
		}

		return result;
	}
}