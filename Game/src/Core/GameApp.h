#pragma once

#include <Core\Application.h>

namespace Game
{
    class CameraController;
    class PlayerController;
    class BallController;

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
        void InitBall();

    private:
        std::unique_ptr<CameraController> m_CameraController{};
        std::unique_ptr<PlayerController> m_PlayerController{};
        std::unique_ptr<BallController> m_BallController{};

    };
}

Engine::Application* Engine::CreateApplication()
{
    return new Game::GameApp();
}
