#pragma once

//typedef  funvoid (*func_t)(Engine::Event*);

namespace Engine
{
    class Event;
    class Channel;
    
    class EventListener
    {
    public:
        void Init() {m_Tracker.clear();}
        void ShutDown() {m_Tracker.clear();}
        void RegisterCallback(Channel*, std::function<void(Event*)> eventCallback);

        template<typename EventType>
        void SendEvent(EventType* e)
        {
            if (e != nullptr)
            {
                if (m_Tracker.count(e->GetChannel()))
                {
                    m_Tracker[e->GetChannel()](e);
                }
            }
        }

    private:
        std::map<Channel*, std::function<void(Event*)>> m_Tracker;
    };
}