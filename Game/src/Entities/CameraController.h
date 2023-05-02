#pragma once

#include <Controller/IController.h>

namespace Game
{
    class CameraController : public Engine::IController
    {
    public:
        void Update(float dt, Engine::EngineSystems& engineSystems) override;
    };
}
