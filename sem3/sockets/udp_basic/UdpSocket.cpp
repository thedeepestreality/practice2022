#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include "UdpSocket.h"

UdpSocket::UdpSocket(std::string const& ip, int port) 
{
    _sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (_sock_fd < 0)
        throw std::runtime_error("failed to open socket");
    _bind_addr.sin_family = AF_INET;
    _bind_addr.sin_port = htons(port);
    if (ip == "any")
        _bind_addr.sin_addr.s_addr = INADDR_ANY;
    else
        _bind_addr.sin_addr.s_addr = inet_addr(ip.c_str());
}

UdpSocket::~UdpSocket()
{
    close(_sock_fd);
}

int UdpSocket::send(std::string const& msg)
{
    int res = send(msg.c_str(), msg.size());
    return res;
}

int UdpSocket::send(const char *buf, size_t sz)
{
    int res = sendto(
        _sock_fd,
        buf,
        sz,
        0,
        reinterpret_cast<sockaddr*>(&_bind_addr),
        ADDR_LEN
    );
    return res;
}

int UdpSocket::recv(char* buf, size_t sz, bool block, int timeout_ns)
{
    int res = 0;
    timeval read_timeout;
    if (!block)
        read_timeout.tv_usec = timeout_ns;
    
    setsockopt(
        _sock_fd, 
        SOL_SOCKET, 
        SO_RCVTIMEO, 
        &read_timeout, 
        sizeof(read_timeout)
    );

    socklen_t len;
    res = recvfrom(
        _sock_fd,
        buf, 
        sz, 
        0, 
        reinterpret_cast<sockaddr*>(&_bind_addr),     
        &len
    );

    return res;
}
