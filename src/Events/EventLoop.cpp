#include "EventLoop.h"
#include "IEventListener.h"

void EventLoop::addEvent(std::shared_ptr<Event> event) {
    m_events.push(event);
}

void EventLoop::addEventListener(std::shared_ptr<IEventListener> eventListener) {
    m_listeners.append(eventListener);
}

void EventLoop::processEvents() {
    std::shared_ptr<Event> event = m_events.pop();
    for (auto it = m_listeners.begin(); it != m_listeners.end(); it++) {
        it.value()->processEvent(event);
        if (event->isAccepted()) break;
    }
}

void EventLoop::discardEvents() {
    while (!m_events.isEmpty()) {
        m_events.pop();
    }
}