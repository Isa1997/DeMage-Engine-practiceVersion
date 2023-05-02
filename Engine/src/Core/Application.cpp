#include "precomp.h"

#include "Application.h"

#include "Render/Renderer.h"
#include "Render/Texture.h"
#include "Render/Window.h"
#include "Render/WindowData.h"
#include <SDL.h>

namespace Engine 
{
    bool Application::Init()
    {
        LOG_INFO("Initializing application");

        GameSpecificWindowData();

        if (m_EngineSystem.Init(m_WindowData) != true)
        {
            LOG_CRITICAL("Error initializing game specific systems!");
            return false;
        } 
        
        if (GameSpecificInit() != true)
        {
            LOG_CRITICAL("Error initializing game specific systems!");
            return false;
        }

        return true;
    }

    bool Application::Shutdown()
    {
        LOG_INFO("Shutting down application");

        GameSpecificShutdown();

        m_EngineSystem.Shutdown();

        return true;
    }

    int Application::Run()
    {
        m_Running = true;
        auto previousFrameTime = SDL_GetPerformanceCounter();

        // Main loop
        SDL_Event event{ };
        while (m_Running)
        {
            while (SDL_PollEvent(&event) != 0)
            {
                if (event.type == SDL_QUIT)
                {
                    m_Running = false;
                }
            }

            auto frameTime = SDL_GetPerformanceCounter();

            float deltaTime = (frameTime - previousFrameTime) / static_cast<float>(SDL_GetPerformanceFrequency());

            LOG_INFO("Current FPS: {}", 1.f / deltaTime);
            Update(deltaTime);

            previousFrameTime = frameTime;
        }

        m_Running = false;

        return 0;
    }

    void Application::Update(float dt)
    {
        m_EngineSystem.Update(dt);

        GameSpecificUpdate(dt);
    }
}
