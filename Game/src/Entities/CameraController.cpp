#include "precomp.h"

#include "CameraController.h"

namespace Game
{
    void CameraController::Update(float dt, Engine::EngineSystems& engineSystems)
    {
        auto entitiesToMove = engineSystems.m_EntityManager->GetAllEntitiesWithComponents<Engine::CameraComponent, Engine::MoverComponent, Engine::InputComponent>();

        for (auto& entity : entitiesToMove)
        {
            // TODO
        }
    }
}
