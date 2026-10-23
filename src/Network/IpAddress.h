#pragma once
#include <string>
class IpAddress {
public:
    IpAddress(const std::string host, unsigned short port);
    std::string host() const;
    unsigned short port() const;
private:
    std::string m_host;
    unsigned short m_port;
};