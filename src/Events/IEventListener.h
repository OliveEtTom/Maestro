#pragma once
#include <memory>
class Event;
class IEventListener {
public:
    ~IEventListener() = default;
    virtual void processEvent(std::shared_ptr<Event> event) = 0;
};