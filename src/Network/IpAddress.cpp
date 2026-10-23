#include "IpAddress.h"

IpAddress::IpAddress(const std::string host, unsigned short  port) : m_host(host), m_port(port) {

}

std::string IpAddress::host() const {
    return m_host;
}

unsigned short IpAddress::port() const {
    return m_port;
}