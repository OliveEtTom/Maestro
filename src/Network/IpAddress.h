#pragma once
#include <string>
class IpAddress {
public:
    IpAddress(const std::string address, size_t port);
private:
    std::string m_address;
    unsigned short m_port;
};