#pragma once

#include <string>


class TcpConnectionHolder
{
public:
    TcpConnectionHolder(int socket);
    ~TcpConnectionHolder();
    TcpConnectionHolder(TcpConnectionHolder&& holder);

    TcpConnectionHolder& operator= (const TcpConnectionHolder&) = delete;
    TcpConnectionHolder() = delete;
    TcpConnectionHolder(const TcpConnectionHolder&) = delete;

    void send_message(const std::string& message) const;
    std::string wait_request();

    bool is_connection_active() const;

private:
    int socket_;
    bool is_connection_active_;
};
