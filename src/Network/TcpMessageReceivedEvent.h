#include "Event.h"
#include <string>
class TcpMessageReceivedEvent : public Event {
public:
    TcpMessageReceivedEvent(const std::string& message);
    std::string message() const;
    Type type() const override;
private:
    std::string m_message;
};