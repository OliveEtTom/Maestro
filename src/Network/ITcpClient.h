#pragma once

#include <boost/asio.hpp>
#include <string>
#include "IpAddress.h"

class ITcpClient
{
public:
    virtual ~ITcpClient() = default;

    virtual boost::asio::awaitable<void> connect(const IpAddress& address) = 0;

    virtual boost::asio::awaitable<void> send(const std::string& message) = 0;

    virtual boost::asio::awaitable<std::string> receive() = 0;

    virtual void close() = 0;

    virtual bool isOpen() const = 0;
};