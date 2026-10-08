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
    size_t m_size;
    size_t m_allocated;
    T* m_rawArray;
    static constexpr float OFFSET = 1.5;
public:
    
    Array(size_t size = 10) : m_size(size), m_rawArray(nullptr) {
        m_allocated = std::round((m_size + 1) * OFFSET);
        if (m_allocated > 0) {
            m_rawArray = new T[m_allocated];
            memset(m_rawArray, 0, m_size * sizeof(T));
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
        delete [] this->m_rawArray;
    }

    size_t size() const {
        return this->m_size;
    }

    Array<T> & operator=(const Array<T>& other) {
        m_size = other.m_size;
        m_allocated = std::round(m_size * OFFSET);
        if (m_allocated > 0) {
            if (m_rawArray != nullptr ) delete [] this->m_rawArray;
            m_rawArray = new T[m_allocated];
            memcpy(m_rawArray, other.m_rawArray, m_size * sizeof(T));
        }
        return *this;
    }

    T & operator[](size_t position) const {
        if (position >= this->m_size) {
            std::stringstream buffer;
            buffer << "Bad position " << position;
            throw std::out_of_range( buffer.str() ); 
        }
        return this->m_rawArray[ position ];
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

    T* data() const { return m_rawArray; }
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