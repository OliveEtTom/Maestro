#pragma once

#include <cstddef>
#include <iostream>
#include <sstream>
#include <stdexcept>

template <class T>
class Array {
    T* m_rawArray;
    size_t m_size;
public:
    
    Array(size_t size = 10) : m_size(size), m_rawArray( new T[m_size] ) {
    }
    
    Array(const Array<T>& original) {
        this->m_rawArray = nullptr;
        *this = original;
    }

    ~Array() {
        delete [] this->m_rawArray;
    }

    size_t size() const {
        return this->m_size;
    }

    Array<T> & operator=( const Array<T> & original ) {
        if ( this->m_rawArray != nullptr ) delete [] this->m_rawArray;
        this->size = original.size;
        this->m_rawArray = new T[this->m_size];
        for( size_t position=0; position<this->size; ++position ) {
            this->m_rawArray[position] = original.m_rawArray[position];
        }

        return *this;
    }

    T & operator[]( size_t position ) const {
        if ( position >= this->m_size ) {
            std::stringstream buffer;
            buffer << "Bad position " << position;
            throw std::out_of_range( buffer.str() ); 
        }
        return this->m_rawArray[ position ];
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