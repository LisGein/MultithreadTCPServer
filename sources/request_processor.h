#pragma once

#include "tcp_connection_holder.h"

#include <memory>


class RequestProcessor
{
public:
    RequestProcessor(std::unique_ptr<TcpConnectionHolder> holder);
    ~RequestProcessor();

    void process_messages();

private:
    std::unique_ptr<TcpConnectionHolder> connection_holder_;
};
