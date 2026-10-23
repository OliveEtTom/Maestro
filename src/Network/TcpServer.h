#pragma once

#include <boost/asio.hpp>
#include <memory>
#include <list>
#include "TcpClient.h"

class TcpServer
    : public std::enable_shared_from_this<TcpServer>
{
public:
    using tcp = boost::asio::ip::tcp;
    using Executor = boost::asio::any_io_executor;

    TcpServer(Executor executor, unsigned short port);

    void start();
    void stop();

    boost::asio::awaitable<void> accept();

    unsigned short port() const;

private:
    boost::asio::awaitable<void> acceptLoop();

    boost::asio::awaitable<void>
    handleClient(std::shared_ptr<TcpClient> client);

    static boost::asio::awaitable<void>
    run(std::shared_ptr<TcpServer> self);

    boost::asio::any_io_executor m_executor;
    tcp::acceptor m_acceptor;
    std::list<std::shared_ptr<TcpClient>> m_clients;
};