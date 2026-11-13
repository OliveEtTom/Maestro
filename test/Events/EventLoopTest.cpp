#include <boost/test/unit_test.hpp>

#include "Event.h"
#include "IEventListener.h"
#include "EventLoop.h"

class MockEvent : public Event {
public:
    ~MockEvent() = default;
    Type type() const override { return Event::User; }
};

class MockEventListener : public IEventListener {
public:
    void processEvent(std::shared_ptr<Event> event) {
        event->accept();
        m_processEventsCount++;
    }
    int processEventsCount() const {
        return m_processEventsCount;
    }
private:
    int m_processEventsCount = 0;
};

BOOST_AUTO_TEST_SUITE(EventLoopTest)

BOOST_AUTO_TEST_CASE(test_processEvents)
{
    // GIVEN an event loop with two listeners that accept the event
    EventLoop eventLoop;
    std::shared_ptr<MockEventListener> listener1 = std::make_shared<MockEventListener>();
    std::shared_ptr<MockEventListener> listener2 = std::make_shared<MockEventListener>();
    eventLoop.addEventListener(listener1);
    eventLoop.addEventListener(listener2);

    // WHEN processing an event
    std::shared_ptr<Event> event = std::make_shared<MockEvent>();
    eventLoop.addEvent(event);
    eventLoop.processEvents();

    // THEN checking that the event was processed by the first listener but NOT by the second
    BOOST_CHECK_EQUAL(listener1->processEventsCount(), 1);
    BOOST_CHECK_EQUAL(listener2->processEventsCount(), 0);

}

BOOST_AUTO_TEST_SUITE_END()