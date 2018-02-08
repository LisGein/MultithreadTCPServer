#pragma once
#include "request_processor.h"
#include <thread>
#include <vector>


class TaskDistributor
{
public:
    TaskDistributor();
    ~TaskDistributor();
    void create_task(int socket);

private:
    std::vector<std::pair<std::unique_ptr<RequestProcessor>, std::thread>> request_processors_;
};
