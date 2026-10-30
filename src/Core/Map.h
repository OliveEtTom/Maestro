#pragma once
#include <memory>
template <class K, class V>
class Map {
private: 
    struct MapNode {
        MapNode(const K& key, const V& value) {
            m_key = key;
            m_value = value;
        }
        K m_key;
        V m_value;
        std::shared_ptr<MapNode> m_left = nullptr;
        std::shared_ptr<MapNode> m_right = nullptr;
    };
public:
    void insert(const K& key, const V& value) {
        if (!m_root) {
            m_root = std::make_unique<MapNode>(key, value);
            return;
        }
        insert(m_root, key, value);
    }

    V value(const K& key, const V& defaultValue = V()) const {
        if (!m_root) return defaultValue;
        return find(m_root, key, defaultValue);
    }
private:
    void insert(std::shared_ptr<MapNode> node, const K& key, const V& value) {
        if (key < node->m_key) {
            if (node->m_left == nullptr) node->m_left = std::make_shared<MapNode>(key, value);
            else insert(node->m_left, key, value);
        }
        else if (key == node->m_key) node->m_value = value;
        else {
            if (node->m_right == nullptr) node->m_right = std::make_shared<MapNode>(key, value);
            else insert(node->m_right, key, value);
        }
    }
    V find(std::shared_ptr<MapNode> node, const K& key, const V& defaultValue) const {
        if (node == nullptr) return defaultValue;
        if (node->m_key == key) return node->m_value;
        else if (key < node->m_key) return find(node->m_left, key, defaultValue);
        return find(node->m_right, key, defaultValue);
    }
    std::shared_ptr<MapNode> m_root = nullptr;
};