#pragma once

#include <fmod.hpp>
#include "Core/System.h"

namespace nc
{
	class AudioSystem : public System
	{
		public:
			virtual bool Startup() override;
			virtual void Shutdown() override;
			virtual void Update() override;
		
			friend class Sound;

		protected:
			FMOD::System* m_system{ nullptr };
	};
}
