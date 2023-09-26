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

    sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    // Filling server information
    servaddr.sin_family    = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    //servaddr.sin_addr.s_addr = inet_addr("192.168.113.97");
    
    servaddr.sin_port = htons(PORT);
       
    // Bind the socket with the server address
    int res = bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr));
    if (res < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // receive data
    sockaddr_in cliaddr;
    memset(&cliaddr, 0, sizeof(cliaddr));
    socklen_t len = sizeof(cliaddr);
    int n = recvfrom(
        sockfd,
        (char *)buffer, 
        BUF_SZ, 
        0, 
        (struct sockaddr *) &cliaddr, 
        &len
    );
    buffer[n] = '\0';
    std::cout << "Message from client: " << buffer << '\n';

    // send response
    sendto(
        sockfd, 
        msg_to_send, 
        strlen(msg_to_send), 
        0, 
        (const struct sockaddr *) &cliaddr, 
        len
    );
    std::cout << "Hello message sent." << std::endl; 
    close(sockfd);
    return 0;
}
