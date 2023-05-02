#pragma once

#include <Core\Application.h>

namespace Game
{
    class CameraController;
    class PlayerController;

    class GameApp final : public Engine::Application
    {
    protected:
        void GameSpecificWindowData() override;
        bool GameSpecificInit() override;
        void GameSpecificUpdate(float dt) override;
        bool GameSpecificShutdown() override;

        void InitTextures();
        void InitAudio();

    private:
        void InitControllers();
        void InitCamera();
        void InitPlayer();

    private:
        std::unique_ptr<CameraController> m_CameraController{};
        std::unique_ptr<PlayerController> m_PlayerController{};
    };
}

Engine::Application* Engine::CreateApplication()
{
    return new Game::GameApp();
}
