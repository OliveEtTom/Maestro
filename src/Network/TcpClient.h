#pragma once

#include "ITcpClient.h"
#include <memory>

class TcpClient : public std::enable_shared_from_this<TcpClient>, public ITcpClient
{
public:
    friend class TcpServer;
    using tcp = boost::asio::ip::tcp;
    TcpClient(tcp::socket socket);

    boost::asio::awaitable<void>
    connect(const IpAddress& address) override;

    boost::asio::awaitable<void>
    send(const std::string& message) override;

    boost::asio::awaitable<std::string>
    receive() override;

    void close() override;

    bool isOpen() const override;

private:
    tcp::socket m_socket;
};