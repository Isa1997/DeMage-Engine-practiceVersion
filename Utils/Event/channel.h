#pragma once

namespace Engine
{
    class EventListener;
    class Event;
}

namespace Engine
{
    class Channel
    {
        //std::map<EEventType, std::vector<EventListener&>> m_Listeners;void (*callback)(const Event*)

    public:
        void RegisterListener(EventListener* listener);
        void UnregisterListener(EventListener* listener);

        template<typename EventType>
        void BroadcastEvent(EventType* e)
        {
            for (EventListener* listener : m_Listeners)
            {
                listener->SendEvent(e);
            }
            delete e;
        }
    private:
            std::vector<EventListener*> m_Listeners;
    };
} // namespace Engine
