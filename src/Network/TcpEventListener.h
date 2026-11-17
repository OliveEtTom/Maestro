#include "IEventListener.h"

class TcpEventListener : public IEventListener {
public:
    void processEvent(std::shared_ptr<Event> event) override;
};