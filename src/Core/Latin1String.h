#pragma once
#include "Array.h"

class Latin1String : public Array<char>
{
public:
    Latin1String(const char* data);
    Latin1String(const char* data, size_t len);
    void toUpper();
    void toLower();
    Latin1String subString(size_t pos, size_t len) const;
    void replace(const Latin1String& pattern, const Latin1String& replacement);
    bool operator==(const Latin1String& other) const;
};
std::ostream & operator<<(std::ostream& os, const Latin1String& string);