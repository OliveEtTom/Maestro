#pragma once
#include "Hash.h"
#include "Array.h"
#include "LinkedList.h"
#include "Latin1String.h"
template <class K, class V>
class HashMap {
private: 
    struct Pair {
        Pair(const K& key, const V& value) {
            m_key = key;
            m_value = value;
        }
        Pair(const Pair& other) {
            m_key = other.m_key;
            m_value = other.m_value;
        }
        Pair() {
            
        }
        K m_key;
        V m_value;
    };
public:
    void insert(const K& key, const V& value) {
        size_t index = hashCode(key);
        Pair pair(key, value);
        while (m_array.size() <= index) {
            m_array.append(LinkedList<Pair>());
        }
        m_array[index].append(pair);
    }

    V value(const K& key, const V& defaultValue) const {
        size_t index = hashCode(key);
        LinkedList<Pair> list = m_array[index];
        for (auto it = list.begin(); it != list.end(); it++) {
            Pair pair = it.value();
            if (pair.m_key == key) return pair.m_value;
        }
        return defaultValue;
    }
    /*V& operator[](const K& key) {
        throw();
    }*/
private:
    size_t hashCode(const K& key) const {
        Hash<K> hash;
        return hash.hashCode(key);
    }
    Array<LinkedList<Pair>> m_array;
};