#pragma once
#include "Latin1String.h"
template<class T>
class Hash {
public:
    size_t hashCode(const T& value) {
        return 0;
    }
};

template<>
class Hash<Latin1String> {
public:
    size_t hashCode(const Latin1String& value) {
        size_t res = 0;
        size_t size = value.size();
        for (size_t iChar = 0; iChar < size; iChar++) {
            size_t weight = static_cast<size_t>(pow(128, size - iChar - 1));
            res += static_cast<size_t>(value[iChar]) * weight;
        }
        return res;
    }
};