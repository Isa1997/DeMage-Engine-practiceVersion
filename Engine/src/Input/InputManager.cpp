#include "precomp.h"

#include "InputManager.h"

#include "ECS/EntityManager.h"

namespace Engine
{
    bool KeyDown(KeyboardButton _iKey)
    {
        short iState = GetAsyncKeyState(static_cast<int>(_iKey));
        return (iState & 0x8000) != 0;
    }

    bool InputManager::Init()
    {
        LOG_INFO("Initializing InputManager");

        InitKeybinds();

        return true;
    }

    void InputManager::ProcessInput()
    {
        for (auto& [action, key] : m_InputActions)
        {
            bool bIsPressed = KeyDown(key);
            switch (m_InputActionStates[action])
            {
            case EInputActionState::None:
            {
                m_InputActionStates[action] = bIsPressed ? EInputActionState::JustPressed : EInputActionState::None;
                break;
            }
            case EInputActionState::JustPressed:
            case EInputActionState::Pressed:
            {
                m_InputActionStates[action] = bIsPressed ? EInputActionState::Pressed : EInputActionState::Released;
                break;
            }
            case EInputActionState::Released:
            {
                m_InputActionStates[action] = bIsPressed ? EInputActionState::JustPressed : EInputActionState::None;
                break;
            }
            default:
                ASSERT("Unknown EInputActionState {0}", m_InputActionStates[action]);
                m_InputActionStates[action] = EInputActionState::None;
                break;
            }
        }
    }

    void InputManager::Update(float dt, EntityManager* entityManager)
    {
        ProcessInput();

        // Update entities
        auto inputComponents = entityManager->GetAllComponentInstances<InputComponent>();

        for (auto component : inputComponents)
        {
            for (auto& action : component->inputActions)
            {
                action.m_Active = IsButtonActionActive(action.m_Action, action.m_ActionTriggerState);
            }
        }
    }

    void InputManager::Shutdown()
    {
        m_InputActions.clear();
        m_InputActionStates.clear();
    }

    bool InputManager::IsButtonActionActive(EInputAction _eAction, EInputActionState _eState) const
    {
        ASSERT(m_InputActionStates.find(_eAction) != m_InputActionStates.end(), "Unknown input action: {}", _eAction);
        return m_InputActionStates.at(_eAction) == _eState;
    }

    void InputManager::InitKeybinds()
    {
        m_InputActionStates.clear();
        m_InputActions.clear();

        m_InputActions["PlayerMoveUp"] = VK_UP;
        m_InputActions["PlayerMoveLeft"] = VK_LEFT;
        m_InputActions["PlayerMoveDown"] = VK_DOWN;
        m_InputActions["PlayerMoveRight"] = VK_RIGHT;
        m_InputActions["PauseGame"] = VK_ESCAPE;
        m_InputActions["RestartGame"] = 'R';
    }

    bool InputManager::IsActionActive(InputComponent* inputComponent, EInputAction targetAction)
    {
        auto found = std::find_if(
            std::begin(inputComponent->inputActions),
            std::end(inputComponent->inputActions),
            [targetAction](Engine::InputAction e)
        {
            return e.m_Action == targetAction && e.m_Active == true;
        });

        return found != std::end(inputComponent->inputActions);
    }
}
