#include <netinet/in.h>
#include <string>
#include <stdexcept>

class UdpSocket
{
private:
    static const socklen_t ADDR_LEN = sizeof(sockaddr_in);
    int _sock_fd;
    sockaddr_in _bind_addr;
public:
    UdpSocket(std::string const& ip, int port);
    ~UdpSocket();
    int send(std::string const& msg);
    int send(const char* buf, size_t sz);
    int recv(char* buf, size_t sz, bool block = true, int timeout_ns = 10);
};