#include "Latin1String.h"
#include <string.h>

Latin1String::Latin1String(const char* data) : Array<char>(data, strlen(data)) {
    //if ((*this)[size() - 1] != '\0') append('\0');
}

void Latin1String::toUpper() {
    char offset = 'a' - 'A';
    for (size_t iChar = 0; iChar < size(); iChar++) {
        if ((*this)[iChar] - 'a' >= 0) (*this)[iChar] = (*this)[iChar] - offset;
    }
}