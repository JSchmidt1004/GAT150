#pragma once

#include <fmod.hpp>
#include "Resources/Resource.h"
#include "AudioChannel.h"

namespace nc
{
	class Sound : public Resource
	{
		public:
			virtual bool Create(const std::string& name, void* data = nullptr) override;
			virtual void Destroy() override;

			AudioChannel Play(bool loop = false);

		private:
			FMOD::System* m_system{ nullptr };
			FMOD::Sound* m_sound{ nullptr };
	};
}
