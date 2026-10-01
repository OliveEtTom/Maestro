#pragma once
#include "Array.h"

class Latin1String : public Array<char>
{
public:
    Latin1String(const char* data);
    void toUpper();
};