#include "task_distributor.h"

#include <iostream>


TaskDistributor::TaskDistributor()
{

}

TaskDistributor::~TaskDistributor()
{
    for (auto &it: request_processors_)
        it.second.join();
}

void TaskDistributor::create_task(int socket)
{
    for (auto it = request_processors_.begin(); it != request_processors_.end(); )
        if (it->second.joinable())
        {
            it->second.join();
            it = request_processors_.erase(it);
        }
        else
            ++it;

    try
    {
        std::unique_ptr<TcpConnectionHolder> holder(new TcpConnectionHolder(socket));
        std::unique_ptr<RequestProcessor> request_processor(new RequestProcessor(std::move(holder)));
        std::thread thread(&RequestProcessor::process_messages, request_processor.get());
        request_processors_.emplace_back(std::move(request_processor), std::move(thread));
    }
    catch (const std::runtime_error& err)
    {
        std::cout << "Caught a runtime_error exception: " << err.what() << std::endl;
    }
}
