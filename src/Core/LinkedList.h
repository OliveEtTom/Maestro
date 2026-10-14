#pragma once
#include <memory>


template <class T>
class LinkedList {
private: 
    struct Node {
        std::shared_ptr<Node> m_next = nullptr;
        T m_data;
    };
public:
    class Iterator {
        friend class LinkedList;
        public:
            T value() { return m_node->m_data; }
            bool operator==(const Iterator& other) const {
                return m_node == other.m_node;
            }
            Iterator& operator++(int) {
                if (m_node) m_node = m_node->m_next;
                return *this;
            }
        private:
            Iterator(std::shared_ptr<Node> node) : m_node(node) {}
            std::shared_ptr<Node> m_node;
    };
    LinkedList() {

    }
    bool isEmpty() const {
        return m_head == nullptr;
    }
    void append(const T& value) {
        if (!m_head) {
            m_head = std::make_unique<Node>();
            m_head->m_data = value;
        }
        else {
            std::shared_ptr<Node> curr = m_head;
            std::shared_ptr<Node> next = m_head->m_next;
            while (next) {
                curr = next;
                next = curr->m_next;
            }
            curr->m_next = std::make_unique<Node>();
            curr->m_next->m_data = value;
        }
    }
    void prepend(const T& value) {
        if (!m_head) {
            m_head = std::make_unique<Node>();
            m_head->m_data = value;
        }
        else {
            std::shared_ptr<Node> newHead = std::make_shared<Node>();
            newHead->m_data = value;
            std::shared_ptr<Node> head = m_head;
            newHead->m_next = head;
            m_head = newHead;
        }
    }
    Iterator begin() {
        return Iterator(m_head);
    }
    Iterator end() {
        if (!m_head) return Iterator(m_head);
        std::shared_ptr<Node> curr = m_head;
        std::shared_ptr<Node> next = m_head->m_next;
        while (next) {
            curr = next;
            next = curr->m_next;
        }
        return Iterator(next);
    }
private:
    std::shared_ptr<Node> m_head = nullptr;
};