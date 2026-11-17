#include "TcpMessageReceivedEvent.h"

TcpMessageReceivedEvent::TcpMessageReceivedEvent(const std::string& message) : m_message(message) {

}

std::string TcpMessageReceivedEvent::message() const {
    return m_message;
}

Event::Type TcpMessageReceivedEvent::type() const {
    return MessageReceived;
}