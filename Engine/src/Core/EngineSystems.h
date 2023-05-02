#pragma once

#include "Audio/AudioSystem.h"
#include "ECS/EntityManager.h"
#include "Input/InputManager.h"
#include "Render/RenderSystem.h"
#include "Render/WindowData.h"
#include "Render/TextureManager.h"
#include "Physics/PhysicsSystem.h"

namespace Engine
{
	struct WindowData;

	struct EngineSystems
	{
	public:

		bool Init(const WindowData& windowData);
		bool Update(float dt);
		bool Shutdown();

		std::unique_ptr<AudioSystem> m_AudioSystem{};
		std::unique_ptr<EntityManager> m_EntityManager{};
		std::unique_ptr<InputManager> m_InputManager{};
		std::unique_ptr<TextureManager> m_TextureManager{};
		std::unique_ptr<PhysicsSystem> m_PhysicsSystem{};
		std::unique_ptr<RenderSystem> m_RenderSystem{};
	};
}

