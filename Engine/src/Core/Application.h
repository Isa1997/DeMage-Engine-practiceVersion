#pragma once

#include "EngineSystems.h"
#include "Render/WindowData.h"

namespace Engine
{
    class Application
    {
    public:
        bool Init();
        int Run();
        bool Shutdown();

        virtual ~Application() = default;
        Application() = default;

    protected:
        void SetWindowData(const WindowData& windowData_) { m_WindowData = windowData_; }

        bool m_Running{ false };

        WindowData m_WindowData{};

        EngineSystems m_EngineSystem;

    private:
        // To be overridden by the game
        virtual void GameSpecificWindowData() = 0;
        virtual bool GameSpecificInit() = 0;
        virtual bool GameSpecificShutdown() = 0;
        virtual void GameSpecificUpdate(float dt) = 0;

        void Update(float dt);

        Application(const Application& other) = delete;
        Application& operator=(Application& other) = delete;
    };

    // To be defined in the game
    Application* CreateApplication();
}
