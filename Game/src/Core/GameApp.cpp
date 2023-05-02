#include "precomp.h"

#include "GameApp.h"

#include <Core/EntryPoint.h>
#include <ECS/Component.h>
#include <Engine.h>
#include "Entities/PlayerController.h"
#include "Entities/CameraController.h"
#include <Logger/Logger.h>

void Game::GameApp::GameSpecificWindowData()
{
    Engine::WindowData gameSpecificWindowData;
    gameSpecificWindowData.m_Title = "Demage";
    gameSpecificWindowData.m_Width = 1280;
    gameSpecificWindowData.m_Height = 720;

    SetWindowData(gameSpecificWindowData);
}

bool Game::GameApp::GameSpecificInit()
{
    m_EngineSystem.m_RenderSystem->SetBackgroundColor(0, 0, 0, 1);

    InitTextures();
    InitAudio();
    InitControllers();

    InitCamera();
    InitPlayer();

    m_EngineSystem.m_AudioSystem->PlayBackgroundMusic("title");
    m_EngineSystem.m_AudioSystem->SetMusicVolume(10);
    m_EngineSystem.m_AudioSystem->SetEffectsVolume(30);

    return true;
}

void Game::GameApp::GameSpecificUpdate(float dt)
{
    m_PlayerController->Update(dt, m_EngineSystem);
    m_CameraController->Update(dt, m_EngineSystem);
}

bool Game::GameApp::GameSpecificShutdown()
{
    return true;
}

void Game::GameApp::InitTextures()
{
    m_EngineSystem.m_TextureManager->CreateTexture(m_EngineSystem.m_RenderSystem->GetRenderer(), "blank", "Data/Sprites/blank.png");
    m_EngineSystem.m_TextureManager->CreateTexture(m_EngineSystem.m_RenderSystem->GetRenderer(), "player", "Data/Sprites/player.jpg");
}

void Game::GameApp::InitAudio()
{
    m_EngineSystem.m_AudioSystem->LoadMusic("Data/Audio/title.wav", "title");
}

void Game::GameApp::InitControllers()
{
    m_PlayerController = std::make_unique<PlayerController>();
    m_CameraController = std::make_unique<CameraController>();
}

void Game::GameApp::InitCamera()
{
    ASSERT(m_EngineSystem.m_EntityManager != nullptr, "Must pass valid pointer to entitymanager to Game::GameApp::InitCamera");

    auto camera = std::make_unique<Engine::Entity>();
    camera->AddComponent<Engine::TransformComponent>();
    camera->AddComponent<Engine::CameraComponent>(100.f);
    camera->AddComponent<Engine::InputComponent>();
    camera->AddComponent<Engine::MoverComponent>();

    auto transformComp = camera->GetComponent<Engine::TransformComponent>();
    transformComp->m_Size = { 1280.f, 720.f };

    m_EngineSystem.m_EntityManager->AddEntity(std::move(camera));
}

void Game::GameApp::InitPlayer()
{
    ASSERT(m_EngineSystem.m_EntityManager.get() != nullptr, "Must pass valid pointer to entitymanager to Game::GameApp::InitPlayer()");

    auto player = std::make_unique<Engine::Entity>();

    player->AddComponent<Engine::TransformComponent>(0.f, 0.f, 100.f, 100.f);
    player->AddComponent<Engine::CollisionComponent>(100.f, 100.f);
    player->AddComponent<Engine::PlayerComponent>();
    player->AddComponent<Engine::InputComponent>();
    player->AddComponent<Engine::MoverComponent>();
    player->AddComponent<Engine::SpriteComponent>().m_Image = m_EngineSystem.m_TextureManager->GetTexture("player");

    auto inputComp = player->GetComponent<Engine::InputComponent>();

    inputComp->inputActions.push_back(std::string("PlayerMoveUp"));
    inputComp->inputActions.push_back(std::string("PlayerMoveDown"));

    m_EngineSystem.m_EntityManager->AddEntity(std::move(player));

}
