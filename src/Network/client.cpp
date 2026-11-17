#include <boost/asio.hpp>
#include <iostream>
#include <string>
#include "TcpClient.h"
#include "EventLoop.h"
#include "TcpEventListener.h"
#include "TcpMessageReceivedEvent.h"

using namespace boost;
using tcp = boost::asio::ip::tcp;

asio::awaitable<void> client(EventLoop& eventLoop)
{
    auto executor = co_await asio::this_coro::executor;
    tcp::socket socket(executor);
    TcpClient client(std::move(socket));
    co_await client.connect(IpAddress("127.0.0.1", 12345));
    std::cout << "Connected\n";
    std::string message = "Hello server!";
    co_await client.send(message);
    std::string received = co_await client.receive();
    eventLoop.addEvent(std::make_shared<TcpMessageReceivedEvent>("Server replied: " + received));
    //eventLoop.stop();
}

int main()
{
    asio::io_context io;
    EventLoop eventLoop;
    std::shared_ptr<TcpEventListener> tcpEventListener = std::make_shared<TcpEventListener>();
    eventLoop.addEventListener(tcpEventListener);

    asio::co_spawn(
        io,
        client(eventLoop),
        asio::detached);

    io.run();
    eventLoop.start();
}