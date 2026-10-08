#include "Latin1String.h"
#include <string.h>

Latin1String::Latin1String(const char* data) : Array<char>(data, strlen(data)) {
}

Latin1String::Latin1String(const char* data, size_t len) : Array<char>(data, len) {
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
    size_t size = this->size();
    if (pos > size || len + pos > size) return "";
    char* data = this->data();
    return Latin1String(data + pos, len);
}

void Latin1String::replace(const Latin1String& pattern, const Latin1String& replacement)
{
    size_t patternSize = pattern.size();
    size_t size = this->size();
    if (patternSize == 0 || patternSize > size) return;
    Latin1String res = "";
    for (size_t iChar = 0; iChar < size; iChar++) {
        Latin1String sub = subString(iChar, patternSize);
        if (sub == pattern) res.append(replacement);
        else res.append(sub);
    }
    *this = res;
}


bool Latin1String::operator==(const Latin1String& other) const
{
    if (size() != other.size()) return false;
    for (size_t iChar = 0; iChar < size(); iChar++) {
        if((*this)[iChar] != other[iChar]) return false;
    }
    return true;
}

std::ostream & operator<<(std::ostream& os, const Latin1String& string)
{
    os << string.data();
    return os;
}