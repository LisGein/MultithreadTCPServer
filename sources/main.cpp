#include "tcp_listener.h"
#include "task_distributor.h"
#include <sys/socket.h>
#include <zconf.h>


int main()
{
    TcpListener listener;
    TaskDistributor taskDistributor;
    while (true)
    {
        int socket = listener.wait_request_for_connection();
        taskDistributor.create_task(socket);
    }

    return 0;
}
