// Server side implementation of UDP client-server model
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
   
const int PORT = 2023;
const int BUF_SZ = 1024;
const char* MULTICAST_ADDR = "224.0.0.0";

int main() 
{
    char buffer[BUF_SZ];
    const char* msg_to_send = "Hello from server";
    
    // Creating socket file descriptor
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) 
    {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    // Filling server information
    addr.sin_family    = AF_INET; // IPv4
    addr.sin_addr.s_addr = inet_addr(MULTICAST_ADDR);
    addr.sin_port = htons(PORT);
    
    socklen_t len = sizeof(addr);
    // send response
    sendto(
        sockfd, 
        msg_to_send, 
        strlen(msg_to_send), 
        0, 
        (const struct sockaddr *) &addr, 
        len
    );
    std::cout << "Hello message sent." << std::endl; 
    close(sockfd);
    return 0;
}
