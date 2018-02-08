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
        connection_holder_->send_message(message);
    }
}

std::string GenerateGetRequest()
{
    std::string request;
    request += "Get / HTTP/1.1\n\r";
    request += "Host: www.lisgein.com\n\r";
    request += "Connection: close\n\r";
    return request;
}
