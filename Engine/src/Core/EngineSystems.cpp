#include "precomp.h"

#include "EngineSystems.h"

#include "Render/WindowData.h"

namespace Engine
{
    bool EngineSystems::Init(const WindowData& windowData)
	{
        // Render system initialize
        m_RenderSystem = std::make_unique<RenderSystem>();
        if (!m_RenderSystem->Init(windowData))
        {
            LOG_CRITICAL("Failed to initialize RenderSystem");
            return false;
        }

        // Texture Manager create
        m_TextureManager = std::make_unique<TextureManager>();

        // Input Manager initialize
        m_InputManager = std::make_unique<InputManager>();
        if (!m_InputManager->Init())
        {
            LOG_CRITICAL("Failed to initialize InputManager");
            return false;
        }

        // Entity Manager initialize
        m_EntityManager = std::make_unique<EntityManager>();
        if (!m_EntityManager->Init())
        {
            LOG_CRITICAL("Failed to initialize EntityManager");
            return false;
        }

        // Physics system initialize
        m_PhysicsSystem = std::make_unique<PhysicsSystem>();
        if (!m_PhysicsSystem->Init())
        {
            LOG_CRITICAL("Failed to initialize PhysicsSystem");
            return false;
        }

        // Audio system initialize
        m_AudioSystem = std::make_unique<AudioSystem>();
        if (!m_AudioSystem->Init())
        {
            LOG_CRITICAL("Failed to initialize PhysicsSystem");
            return false;
        }
        return true;
	}

	bool EngineSystems::Update(float dt)
	{
        m_InputManager->Update(dt, m_EntityManager.get());
        m_PhysicsSystem->Update(dt, m_EntityManager.get());
        m_EntityManager->Update(dt);
        m_RenderSystem->Update(dt, m_EntityManager.get());

        return true;
	}

	bool EngineSystems::Shutdown()
	{
        m_AudioSystem->Shutdown();
        m_AudioSystem.reset();

        m_EntityManager->Shutdown();
        m_EntityManager.reset();

        m_InputManager->Shutdown();
        m_InputManager.reset();

        m_RenderSystem->Shutdown();
        m_RenderSystem.reset();

        m_TextureManager->Shutdown();
        m_TextureManager.reset();

        return true;
	}
}
