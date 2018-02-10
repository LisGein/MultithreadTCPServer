#include "request_processor.h"

#include <stdexcept>
#include <iostream>


RequestProcessor::RequestProcessor(std::unique_ptr<TcpConnectionHolder> holder)
    : connection_holder_(std::move(holder))
{
}

RequestProcessor::~RequestProcessor()
{
}

void RequestProcessor::process_messages()
{
    while (true)
    {
        const std::string message = connection_holder_->wait_request();
        if (!connection_holder_->is_connection_active())
            break;

        connection_holder_->send_message(message);
    }
}
