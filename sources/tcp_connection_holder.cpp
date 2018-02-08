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

void TcpConnectionHolder::send_message(const std::string &message)
{
    send(socket_, message.c_str(), sizeof(message.at(0)) * message.size(), 0);
}

std::string TcpConnectionHolder::wait_request()
{
    const int sizeOfBuffer = 1024;
    char buf[sizeOfBuffer];
    int sizeOfBytes = recv(socket_, buf, sizeOfBuffer, 0);
    if (sizeOfBytes <= 0)
    {
        is_connection_active_ = false;
        return std::string();
    }

    uint size_of_message = 0;
    try
    {
        size_of_message = std::stoi(std::string(buf, sizeOfBuffer));
    }
    catch (std::invalid_argument&)
    {
        send_message("Invalid size of message");
        return wait_request();
    }

    std::string data;
    while (size_of_message > data.size())
    {
        int bytes = recv(socket_, buf, sizeOfBuffer, 0);
        data += std::string(buf, bytes);
    }
    return data;
}
