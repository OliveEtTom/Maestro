#include <boost/asio.hpp>
#include <iostream>
#include <string>

using namespace boost;
using asio::ip::tcp;

asio::awaitable<void> handle_client(tcp::socket socket)
{
    try
    {
        std::cout << "Client connected\n";

        char buffer[1024];

        for (;;)
        {
            std::size_t n =
                co_await socket.async_read_some(
                    asio::buffer(buffer),
                    asio::use_awaitable);

            std::string message(buffer, n);

            std::cout << "Received: " << message << '\n';

            // Echo
            co_await asio::async_write(
                socket,
                asio::buffer(message),
                asio::use_awaitable);
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "Client disconnected: "
                  << e.what() << '\n';
    }
}

asio::awaitable<void> server()
{
    auto executor = co_await asio::this_coro::executor;

    tcp::acceptor acceptor(
        executor,
        tcp::endpoint(tcp::v4(), 12345));

    std::cout << "Server listening on port 12345\n";

    for (;;)
    {
        tcp::socket socket =
            co_await acceptor.async_accept(
                asio::use_awaitable);

        asio::co_spawn(
            executor,
            handle_client(std::move(socket)),
            asio::detached);
    }
}

int main()
{
    asio::io_context io;

    asio::co_spawn(
        io,
        server(),
        asio::detached);

    io.run();
}