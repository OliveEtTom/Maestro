#include "ConcurrentQueue.h"
#include "LinkedList.h"
#include "Event.h"
#include <memory>
class IEventListener;
class EventLoop {
public:
    void addEvent(std::shared_ptr<Event> event);
    void addEventListener(std::shared_ptr<IEventListener> eventListener);
    void processEvents();
    void discardEvents();
private:
    ConcurrentQueue<std::shared_ptr<Event>> m_events;
    LinkedList<std::shared_ptr<IEventListener>> m_listeners;
};