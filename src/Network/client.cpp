#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include "TcpClient.h"

using namespace boost;
using tcp = boost::asio::ip::tcp;

asio::awaitable<void> client()
{
    auto executor = co_await asio::this_coro::executor;
    tcp::socket socket(executor);
    TcpClient client(std::move(socket));
    co_await client.connect(IpAddress("127.0.0.1", 12345));
    std::cout << "Connected\n";
    std::string message = "Hello server!";
    co_await client.send(message);
    std::string received = co_await client.receive();
    std::cout << "Server replied: "
              << received
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