#pragma once

#include <boost/asio.hpp>
#include <string>
#include "IpAddress.h"
#include <memory>

class ITcpClient;
class ITcpServer {
    public:
        virtual ~ITcpServer() = default;
        virtual boost::asio::awaitable<void> bind(const IpAddress& address) = 0;
        virtual boost::asio::awaitable<std::shared_ptr<ITcpClient>> accept() = 0;
};