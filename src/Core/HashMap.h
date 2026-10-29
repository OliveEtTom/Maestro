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

        Pair& operator=(const Pair& other) {
            m_key = other.m_key;
            m_value = other.m_value;
            return *this;
        }

        K m_key;
        V m_value;
    };
public:
    void insert(const K& key, const V& value) {
        size_t hash = hashCode(key);
        size_t index = hash % size();
        if (index == size()) {
            resize();
            index = hash % size();
        }
        LinkedList<Pair>& values = m_array[index];
        Pair pair(key, value);
        values.append(pair);
    }

    V value(const K& key, const V& defaultValue = V()) const {
        size_t hash = hashCode(key);
        size_t index = hash % m_array.size();
        LinkedList<Pair>& list = m_array[index];
        for (auto it = list.begin(); it != list.end(); it++) {
            Pair pair = it.value();
            if (pair.m_key == key) return pair.m_value;
        }
        return defaultValue;
    }
    
    /*V& operator[](const K& key) const {
        return value(key);
    }*/

    size_t size() const {
        return m_array.size();
    }
private:
    void resize() {
        Array<LinkedList<Pair>> newArray(size() + 1);
        newArray.append(LinkedList<Pair>());
        for (size_t idx = 0; idx < m_array.size(); idx++) {
            LinkedList<Pair>& list = m_array[idx];
            for (auto it = list.begin(); it != list.end(); it++) {
                Pair pair = it.value();
                size_t hash = hashCode(pair.m_key);
                size_t index = hash % newArray.size();
                newArray[index].append(pair);
            }
        }
        m_array = newArray;
    }
    size_t hashCode(const K& key) const {
        Hash<K> hash;
        return hash.hashCode(key);
    }
    Array<LinkedList<Pair>> m_array = Array<LinkedList<Pair>>(1);
};