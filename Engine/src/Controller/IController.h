#pragma once

#include "Core/EngineSystems.h"

namespace Engine
{
	class IController
	{
	public:
		virtual ~IController() {}
		virtual void Start() {}
		virtual void Update(float dt, EngineSystems& engine) = 0;
		virtual void Shutdown() {}
	};
}