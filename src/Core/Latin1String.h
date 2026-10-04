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
};