#pragma once

namespace Engine
{
    class Channel;

    class Event
    {
    public:
        virtual void Broadcast() = 0;
        virtual Channel* GetChannel() = 0;
        virtual ~Event() {}
    };
}