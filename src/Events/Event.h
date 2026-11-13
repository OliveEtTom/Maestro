#pragma once
class Event {
public:
    enum Type {
        User = 256
    };
    virtual ~Event() = default;
    virtual Type type() const = 0;
    bool isAccepted() const { return m_accepted; }
    void accept() { m_accepted = true; }
private:
    bool m_accepted = false;
};