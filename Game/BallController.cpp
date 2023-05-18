#include "precomp.h"
#include "BallController.h"

#include "src/Entities/GameComponents.h"

namespace Game
{
    void BallController::Update(float dt, Engine::EngineSystems& engineSystems)
    {
        auto entitiesToMove = engineSystems.m_EntityManager->
            GetAllEntitiesWithComponents<Game::BallComponent, Engine::MoverComponent,Engine::TransformComponent>();

        for (auto& entity : entitiesToMove)
        {
            auto transformComponent = entity->GetComponent<Engine::TransformComponent>();
            auto moverComponent = entity->GetComponent<Engine::MoverComponent>();
            if (transformComponent->m_Position.x > 640)
            {
                moverComponent->m_TranslationSpeed.x = -50;
            }
            else if (transformComponent->m_Position.x < -640)
            {
                moverComponent->m_TranslationSpeed.x = 50;
            }

            if (transformComponent->m_Position.y > 360)
            {
                moverComponent->m_TranslationSpeed.y = -50;
            }
            else if (transformComponent->m_Position.y < -360)
            {
                moverComponent->m_TranslationSpeed.y = 50;
            }
        }
    }
}