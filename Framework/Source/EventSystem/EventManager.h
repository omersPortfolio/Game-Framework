#pragma once

namespace fw {

class Event;
class GameCore;

class EventManager
{
public:
    EventManager();
    ~EventManager();

    void AddEvent(Event* pEvent, float delayBeforeSending = 0.0f);
    void DispatchAllEvents(float deltaTime, GameCore* pGameCore);

protected:
    std::queue<Event*> m_EventQueue;
};

} // namespace fw
