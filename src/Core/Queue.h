#pragma once
#include <memory>
template<class T>
class Queue {
private:
    struct Node {
        Node(T data) : m_data(data) {}
        T m_data;
        std::shared_ptr<Node> m_next = nullptr;
    };
public:
    bool isEmpty() {
        return m_first == nullptr;
    }
    void push(const T& value) {
        std::shared_ptr<Node> t = std::make_shared<Node>(value);
        if (m_last) {
            m_last->m_next = t;
        }
        m_last = t;
        if (!m_first) {
            m_first = m_last;
        }
    }
    T pop() {
        if (isEmpty()) throw;
        T value = m_first->m_data;
        m_first = m_first->m_next;
        if (!m_first) m_last = nullptr;
        return value;
    }
private:
    std::shared_ptr<Node> m_first = nullptr;
    std::shared_ptr<Node> m_last = nullptr;
};
