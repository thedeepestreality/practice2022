// Client side implementation of UDP client-server model
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

const int PORT = 2023;
const int BUF_SZ = 1024;
const char* MULTICAST_ADDR = "224.0.0.0";
const char* INTERFACE_ADDR = "192.168.0.104";

int main() 
{
    char buffer[BUF_SZ];
    const char* msg_to_send = "Hello from client";
    
    // Creating socket file descriptor
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    // Filling server information
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket with the server address
    int res = bind(sockfd, (const struct sockaddr *)&addr, sizeof(addr));
    if (res < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    struct ip_mreq mreq;
    mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_ADDR);
    mreq.imr_interface.s_addr = inet_addr(INTERFACE_ADDR);
    res = setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

    // struct timeval read_timeout;
    // read_timeout.tv_sec = 0;
    // read_timeout.tv_usec = 0;
    // setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &read_timeout, sizeof read_timeout);

    socklen_t len = sizeof(addr);
    int n = recvfrom(
        sockfd, 
        (char *)buffer, 
        BUF_SZ, 
        0, 
        (struct sockaddr *) &addr,     
        &len
    );

    if (n < 0)
    {
        perror("socket read nothing");
        exit(EXIT_FAILURE);
    }

    buffer[n] = '\0';
    std::cout << "Message from server: " << buffer << "\n";
   
    close(sockfd);
    return 0;
}