#pragma once
#include "src/ECS/Component.h"

namespace Game
{
    struct TestComponent : public Engine::Component
    {

    };

    struct BallComponent : public Engine::Component
    {
        std::string m_Name;
    };
}