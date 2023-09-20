#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

const int PORT = 2023;

int main(int argc, char const* argv[])
{
	const char* hello = "Hello from client";
	char buffer[1024] = { 0 };
    int client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (client_fd < 0) {
		perror("Socket creation error");
		exit(EXIT_FAILURE);
	}

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    int status = connect(
        client_fd, 
        (struct sockaddr*)&servaddr,
		sizeof(servaddr)
    );
	if (status < 0) 
    {
        perror("Connection Failed");
		exit(EXIT_FAILURE);
	}
	send(client_fd, hello, strlen(hello), 0);
	std::cout << "Hello message sent\n";
	int valread = read(client_fd, buffer, 1024);
	std::cout << "Message from server: " << buffer << '\n';

	// closing the connected socket
	close(client_fd);
	return 0;
}
