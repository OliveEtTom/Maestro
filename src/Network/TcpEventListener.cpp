#include "TcpEventListener.h"
#include "TcpMessageReceivedEvent.h"
#include "iostream"
void TcpEventListener::processEvent(std::shared_ptr<Event> event) {
    if (TcpMessageReceivedEvent* tcpEvent = dynamic_cast<TcpMessageReceivedEvent*>(event.get())) {
        std::cout << "TcpEventListener::processEvent" << '\n';
        std::cout << tcpEvent->message() << '\n';
    }
}