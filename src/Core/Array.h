#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <cmath>
#include <string.h>

template <class T>
class Array {
private:
    size_t m_size = 0;
    size_t m_allocated = 0;
    T* m_rawArray = nullptr;
    static constexpr float OFFSET = 1.5;
public:
    
    Array(size_t size = 0) : m_size(size), m_rawArray(nullptr) {
        m_allocated = std::round((m_size + 1) * OFFSET);
        if (m_allocated > 0) {
            m_rawArray = new T[m_allocated];
            fill(0, m_size);
        }
    }
    
    Array(const Array<T>& other) {
        m_size = other.m_size;
        m_allocated = other.m_allocated;
        if (m_allocated > 0) {
            m_rawArray = new T[m_allocated];
            memcpy(m_rawArray, other.m_rawArray, m_size * sizeof(T));
            memset(m_rawArray + m_size, 0, (m_allocated - m_size) * sizeof(T));
        }
    }

    Array(const T* rawArray, size_t size) {
        m_size = size;
        m_allocated = std::round((m_size + 1) * OFFSET);
        if (m_allocated > 0) {
            m_rawArray = new T[m_allocated];
            memcpy(m_rawArray, rawArray, m_size * sizeof(T));
            memset(m_rawArray + m_size, 0, (m_allocated - m_size) * sizeof(T));
        }
    }

    ~Array() {
        delete [] m_rawArray;
    }

    size_t size() const {
        return m_size;
    }

    size_t allocated() const {
        return m_allocated;
    }

    void clear() {
        delete [] m_rawArray;
        m_rawArray = nullptr;
        m_size = 0;
        m_allocated = std::round((m_size + 1) * OFFSET);
        if (m_allocated > 0) {
            m_rawArray = new T[m_allocated];
        }
    }

    Array<T>& operator=(const Array<T>& other) {
        m_size = other.m_size;
        m_allocated = std::round(m_size * OFFSET);
        if (m_allocated > 0) {
            if (m_rawArray != nullptr ) delete [] this->m_rawArray;
            m_rawArray = new T[m_allocated];
            for (size_t index = 0; index < m_size; index++) m_rawArray[index] = other.m_rawArray[index];
        }
        return *this;
    }

    T & operator[](size_t index) const {
        return m_rawArray[index];
    }

    void append(const Array<T>& other) {
        if (other.m_size == 0 || other.m_rawArray == nullptr) return;
        size_t newSize = m_size + other.m_size;
        if (m_allocated < newSize) {
            m_allocated = std::round(newSize * OFFSET);
            T* rawArray = new T[m_allocated];
            memcpy(rawArray, m_rawArray, m_size * sizeof(T));
            memcpy(rawArray + m_size, other.m_rawArray, other.m_size * sizeof(T));
            if (m_rawArray) delete m_rawArray;
            m_rawArray = rawArray;
        }
        else {
            memcpy(m_rawArray + m_size, other.m_rawArray, other.m_size * sizeof(T));
        }
        m_size = newSize;
    }

    void append(const T& value) {
        size_t newSize = m_size + 1;
        if (m_allocated < newSize) {
            m_allocated = std::round(newSize * OFFSET);
            T* rawArray = new T[m_allocated];
            for (size_t index = 0; index < m_size; index++) rawArray[index] = m_rawArray[index];
            rawArray[m_size] = value;
            if (m_rawArray) delete [] m_rawArray;
            m_rawArray = rawArray;
        }
        else {
            m_rawArray[m_size] = value;
        }
        m_size = newSize;
    }

    T* data() const { return m_rawArray; }

    void resize(size_t newSize) {
        m_allocated = std::round((newSize + 1) * OFFSET);
        if (newSize == 0) {
            m_size = newSize;
            if (m_rawArray) delete [] m_rawArray;
            m_rawArray = nullptr;
        }
        else {
            T* rawArray = new T[m_allocated];
            if (newSize > m_size) {
                for (size_t i = 0; i < m_size; i++) {
                    rawArray[i] = m_rawArray[i];
                }
            }
            else {
                for (size_t i = 0; i < newSize; i++) {
                    rawArray[i] = m_rawArray[i];
                }
            }
            if (m_rawArray) delete [] m_rawArray;
            m_rawArray = rawArray;
            if (newSize > m_size) fill(m_size, newSize);
            m_size = newSize;
        }
    }
private:
    void fill(size_t start, size_t end) {
        for (size_t i = start; i < end; i++) {
            m_rawArray[i] = T();
        }
    }
};

template <class T>
std::ostream & operator<<( std::ostream & os, const Array<T> & array ) {
    os << "[";
    size_t size = array.size();
    for( size_t position=0; position<size; ++position ) {
        os << array[position];
        if ( position < size-1 ) os << ", ";
    }
    return os << "]";
}