#include "TcpClient.h"

TcpClient::TcpClient(tcp::socket socket) : m_socket(std::move(socket)) {

}

void TcpClient::write(const std::string message) {
    /*co_await asio::async_write(
            m_socket,
            asio::buffer(message),
            asio::use_awaitable);*/
}

std::string TcpClient::read(size_t maxSize) {
    /*char buffer[1024];
    std::size_t n =
        co_await m_socket.async_read_some(
            asio::buffer(buffer),
            asio::use_awaitable);
    return buffer;*/
    return "";
}