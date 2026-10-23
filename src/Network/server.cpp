#include "TcpServer.h"

#include <boost/asio.hpp>
#include <iostream>

int main()
{
    boost::asio::io_context io;

    auto server = std::make_shared<TcpServer>(
        io.get_executor(),
        0  // Let the OS choose an available port
    );

    server->start();

    std::cout << "Listening on port "
              << server->port() << '\n';

    io.run();
}