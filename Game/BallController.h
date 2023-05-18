#pragma once
#include <Controller/IController.h>

namespace Game
{
    class BallController : public Engine::IController
    {
    public:
        void Update(float dt, Engine::EngineSystems& engine) override;
    };
}

