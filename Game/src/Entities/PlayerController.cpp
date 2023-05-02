#include "precomp.h"

#include "PlayerController.h"

namespace Game
{
    void PlayerController::Update(float dt, Engine::EngineSystems& engineSystem)
    {
        auto entitiesToMove = engineSystem.m_EntityManager->GetAllEntitiesWithComponents<Engine::PlayerComponent, Engine::MoverComponent, Engine::InputComponent>();

        for (auto& entity : entitiesToMove)
        {
            auto move = entity->GetComponent<Engine::MoverComponent>();
            auto input = entity->GetComponent<Engine::InputComponent>();
            float speed = 50.0f;

            bool moveUpInput = Engine::InputManager::IsActionActive(input, fmt::format("PlayerMoveUp"));
            bool moveDownInput = Engine::InputManager::IsActionActive(input, fmt::format("PlayerMoveDown"));

            move->m_TranslationSpeed.y = speed * ((moveUpInput ? -1.0f : 0.0f) + (moveDownInput ? 1.0f : 0.0f));
        }
    }
}
