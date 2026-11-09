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
            m_root = std::make_shared<MapNode>(key, value);
            return;
        }
        insert(m_root, key, value);
    }

    bool remove(const K& key) {
        std::shared_ptr<MapNode> parentNode = nullptr;
        std::shared_ptr<MapNode> node = findNode(m_root, key, &parentNode);
        if (!node || !parentNode) return false;
        std::shared_ptr<MapNode> left = node->m_left;
        std::shared_ptr<MapNode> right = node->m_right;
        bool isLeftChild = node == parentNode->m_left;
        if (isLeftChild) {
            parentNode->m_left = left;
            left->m_right = right;
        }
        else {
            parentNode->m_right = right;
            right->m_left = left;
        }
        return true;
    }

    V value(const K& key, const V& defaultValue = V()) const {
        std::shared_ptr<MapNode> parentNode = nullptr;
        std::shared_ptr<MapNode> node = findNode(m_root, key, &parentNode);
        if (!node) return defaultValue;
        return node->m_value;
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

    std::shared_ptr<MapNode> findNode(std::shared_ptr<MapNode> node, const K& key, std::shared_ptr<MapNode>* parent) const {
        if (node == nullptr) return nullptr;
        if (node->m_key == key) return node;
        else {
            if(parent) *parent = node;
            if (key < node->m_key) return findNode(node->m_left, key, parent);
            return findNode(node->m_right, key, parent);
        }
    }

    std::shared_ptr<MapNode> m_root = nullptr;
};