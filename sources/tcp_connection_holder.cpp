#include "tcp_connection_holder.h"

#include <iostream>
#include <stdexcept>
#include <sys/socket.h>
#include <zconf.h>


TcpConnectionHolder::TcpConnectionHolder(int socket)
    : socket_(socket)
    , is_connection_active_(true)
{
    if (socket_ < 0)
        throw std::runtime_error("Socket less 0: " + std::to_string(socket_));

}

TcpConnectionHolder::~TcpConnectionHolder()
{
    close(socket_);
}

TcpConnectionHolder::TcpConnectionHolder(TcpConnectionHolder &&holder)
{
    std::swap(holder.socket_, socket_);
    std::swap(holder.is_connection_active_, is_connection_active_);
}

void TcpConnectionHolder::send_message(const std::string &message) const
{
    send(socket_, message.c_str(), sizeof(message.at(0)) * message.size(), 0);
}

std::string TcpConnectionHolder::wait_request()
{
    const int size_of_buffer = 1024;
    char buf[size_of_buffer];
    int size_of_bytes = recv(socket_, buf, size_of_buffer, 0);
    if (size_of_bytes <= 0)
    {
        is_connection_active_ = false;
        return std::string();
    }

    uint size_of_message = 0;
    try
    {
        size_of_message = std::stoi(std::string(buf, size_of_buffer));
    }
    catch (std::invalid_argument&)
    {
        send_message("Invalid size of message");
        return wait_request();
    }

    std::string data;
    while (size_of_message > 0)
    {
        ssize_t bytes = recv(socket_, buf, size_of_buffer, 0);
        uint size_of_recv_data = bytes < size_of_message ? bytes : size_of_message;
        data += std::string(buf, size_of_recv_data);
        size_of_message -= size_of_recv_data;
    }
    return data;
}

bool TcpConnectionHolder::is_connection_active() const
{
    return is_connection_active_;
}
