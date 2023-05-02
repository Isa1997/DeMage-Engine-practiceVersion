#pragma once

#include <Controller/IController.h>

namespace Game
{
    class PlayerController : public Engine::IController
    {
    public:
        void Update(float dt, Engine::EngineSystems& engineSystems) override;
    };
}