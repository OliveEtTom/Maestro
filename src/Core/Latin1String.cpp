#include "Latin1String.h"
#include <string.h>

Latin1String::Latin1String(const char* data) : Array<char>(data, strlen(data)) {
    //if ((*this)[size() - 1] != '\0') append('\0');
}

Latin1String::Latin1String(const char* data, size_t len) : Array<char>(data, len) {
    //if ((*this)[size() - 1] != '\0') append('\0');
}

void Latin1String::toUpper() {
    char offset = 'a' - 'A';
    for (size_t iChar = 0; iChar < size(); iChar++) {
        if ((*this)[iChar] - 'a' >= 0) (*this)[iChar] = (*this)[iChar] - offset;
    }
}

void Latin1String::toLower() {
    char offset = 'a' - 'A';
    for (size_t iChar = 0; iChar < size(); iChar++) {
        if ((*this)[iChar] - 'a' < 0) (*this)[iChar] = (*this)[iChar] + offset;
    }
}


Latin1String Latin1String::subString(size_t pos, size_t len) const
{
    if (pos >= size() || len-pos >= size()) return "";
    char* data = this->data();
    return Latin1String(data + pos, len);
}