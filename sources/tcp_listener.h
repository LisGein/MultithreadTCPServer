#pragma once


class TcpListener
{
public:
    TcpListener();
    int wait_request_for_connection();

private:
    const int listener_;
};
