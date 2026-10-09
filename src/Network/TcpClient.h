#pragma once
#include <memory>
#include <string>
#include <boost/asio.hpp>
using namespace boost;
using asio::ip::tcp;
class TcpClient
{
public:
    TcpClient(tcp::socket socket);
    void write(const std::string message);
    std::string read(size_t maxSize);
private:
    tcp::socket m_socket;
};