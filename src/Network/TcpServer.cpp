#include "TcpServer.h"

#include <iostream>
#include <string>
#include "TcpClient.h"

namespace asio = boost::asio;

TcpServer::TcpServer(
    Executor executor,
    unsigned short port)
    : m_executor(executor),
      m_acceptor(
          m_executor,
          tcp::endpoint(
              asio::ip::address_v4::loopback(),
              port))
{
}

unsigned short TcpServer::port() const
{
    return m_acceptor.local_endpoint().port();
}

void TcpServer::start()
{
    auto self = shared_from_this();

    asio::co_spawn(
        m_executor,
        run(std::move(self)),
        asio::detached);
}

void TcpServer::stop()
{
    boost::system::error_code ec;
    m_acceptor.close(ec);
}

boost::asio::awaitable<void> TcpServer::accept() {
    tcp::socket socket(m_executor);
    co_await m_acceptor.async_accept(
        socket,
        asio::use_awaitable);

    std::shared_ptr<TcpClient> client = std::make_shared<TcpClient>(std::move(socket));
    m_clients.push_back(client);
}

asio::awaitable<void>
TcpServer::run(std::shared_ptr<TcpServer> self)
{
    try {
        co_await self->acceptLoop();
    }
    catch (const boost::system::system_error& e) {
        if (e.code() != asio::error::operation_aborted) {
            std::cerr << "TCP server error: "
                      << e.what() << '\n';
        }
    }
    catch (const std::exception& e) {
        std::cerr << "TCP server error: "
                  << e.what() << '\n';
    }
}

asio::awaitable<void> TcpServer::acceptLoop()
{
    while (m_acceptor.is_open()) {
        co_await accept();
        asio::co_spawn(
            m_executor,
            handleClient(*m_clients.end()),
            asio::detached);
    }
}

asio::awaitable<void>
TcpServer::handleClient(std::shared_ptr<TcpClient> client)
{
    try {
        while (client->isOpen()) {
            asio::streambuf buffer;

            std::string message = co_await client->receive();
            message += '\n';

            co_await client->send(message);
            m_clients.push_back(client);
        }
    }
    catch (const boost::system::system_error&) {
        // The client disconnected or the connection failed.
        // This handler ends without affecting other clients.
    }
}