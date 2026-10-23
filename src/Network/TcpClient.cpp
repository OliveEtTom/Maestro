#include "TcpClient.h"

#include <boost/asio/experimental/awaitable_operators.hpp>

#include <array>
#include <stdexcept>

namespace asio = boost::asio;

TcpClient::TcpClient(tcp::socket socket)
    : m_socket(std::move(socket))
{
}

asio::awaitable<void>
TcpClient::connect(const IpAddress& address)
{
    auto executor = co_await asio::this_coro::executor;

    tcp::resolver resolver(executor);
    auto endpoints = co_await resolver.async_resolve(
        address.host(),
        std::to_string(address.port()),
        asio::use_awaitable
    );

    co_await asio::async_connect(
        m_socket,
        endpoints,
        asio::use_awaitable
    );
}

asio::awaitable<void>
TcpClient::send(const std::string& message)
{
    co_await asio::async_write(
        m_socket,
        asio::buffer(message),
        asio::use_awaitable
    );
}

asio::awaitable<std::string>
TcpClient::receive()
{
    std::array<char, 1024> buffer{};

    const auto size = co_await m_socket.async_read_some(
        asio::buffer(buffer),
        asio::use_awaitable
    );

    co_return std::string(buffer.data(), size);
}

void TcpClient::close()
{
    boost::system::error_code ec;
    m_socket.close(ec);
}

bool TcpClient::isOpen() const
{
    return m_socket.is_open();
}