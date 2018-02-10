#include "tcp_listener.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdexcept>


TcpListener::TcpListener()
    : listener_(socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))
{
    if (listener_ < 0)
        throw std::runtime_error("Error create file descriptor for new socket!");

    const int option = 1;
    setsockopt(listener_, SOL_SOCKET, SO_REUSEPORT, &option, sizeof(option));

    sockaddr_in address{AF_INET, htons(8080), htonl(INADDR_ANY)};
    const socklen_t len = sizeof(address);
    const int result = bind(listener_, reinterpret_cast<sockaddr*>(&address), len);
    if (result < 0)
        throw std::runtime_error("Error assigning a name to a socket!");

    listen(listener_, 1);
}

int TcpListener::wait_request_for_connection()
{
    return accept(listener_, nullptr, nullptr);
}
