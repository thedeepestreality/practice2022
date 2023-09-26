#include <iostream>
#include "UdpSocket.h"

const int PORT = 2023;
const int BUF_SZ = 1024;
const std::string IP = "any";

int main()
{
    char buffer[BUF_SZ];
    const char* msg_to_send = "Hello from client";
    
    UdpSocket udp(IP, PORT);
    udp.send(msg_to_send);
    std::cout<<"Message sent to server\n";

    int n = udp.recv(buffer, BUF_SZ);
    if (n < 0)
    {
        perror("socket read nothing");
        exit(EXIT_FAILURE);
    }
    buffer[n] = '\0';
    std::cout << "Message from server: " << buffer << "\n";
    return 0;
}