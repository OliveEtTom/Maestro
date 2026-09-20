#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost;
using asio::ip::tcp;

asio::awaitable<void> client()
{
    auto executor = co_await asio::this_coro::executor;

    tcp::socket socket(executor);

    tcp::resolver resolver(executor);

    auto endpoints =
        co_await resolver.async_resolve(
            "127.0.0.1",
            "12345",
            asio::use_awaitable);

    co_await asio::async_connect(
        socket,
        endpoints,
        asio::use_awaitable);

    std::cout << "Connected\n";

    std::string message = "Hello server!";

    co_await asio::async_write(
        socket,
        asio::buffer(message),
        asio::use_awaitable);

    char buffer[1024];

    std::size_t n =
        co_await socket.async_read_some(
            asio::buffer(buffer),
            asio::use_awaitable);

    std::cout << "Server replied: "
              << std::string(buffer, n)
              << '\n';
}

int main()
{
    asio::io_context io;

    asio::co_spawn(
        io,
        client(),
        asio::detached);

    io.run();
}