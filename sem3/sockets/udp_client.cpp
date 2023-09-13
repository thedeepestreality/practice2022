
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

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    // Filling server information
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;
    
    socklen_t len = sizeof(servaddr);
    sendto(
        sockfd,
        msg_to_send,
        strlen(msg_to_send),
        0,
        (const struct sockaddr *) &servaddr,
        len
    );
    std::cout<<"Message sent to server\n";

    int n = recvfrom(
        sockfd, 
        (char *)buffer, 
        BUF_SZ, 
        0, 
        (struct sockaddr *) &servaddr,     
        &len
    );
    buffer[n] = '\0';
    std::cout << "Message from server: " << buffer << "\n";
   
    close(sockfd);
    return 0;
}