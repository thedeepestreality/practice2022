// Server side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
const int PORT = 2023;

int main(int argc, char const* argv[])
{
	int valread;
	int opt = 1;
    const char* hello = "Hello from server";
	char buffer[1024] = { 0 };
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	// Creating socket file descriptor
	if (server_fd < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	// Forcefully attaching socket to the port 8080
    int res;
    // int res = setsockopt(
    //     server_fd, 
    //     SOL_SOCKET,
	// 	SO_REUSEADDR | SO_REUSEPORT, 
    //     &opt,
	// 	sizeof(opt)
    // );
	// if (res < 0) {
	// 	perror("setsockopt");
	// 	exit(EXIT_FAILURE);
	// }
    struct sockaddr_in address;
    int addrlen = sizeof(address);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
    res = bind(
        server_fd, 
        (struct sockaddr*)&address,
		sizeof(address)
    );
	if (res	< 0) {
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

    res = listen(server_fd, 3);
	if (res < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

    int new_socket = accept(
        server_fd, 
        (struct sockaddr*)&address,
		(socklen_t*)&addrlen
    );
	if (new_socket < 0) {
		perror("accept");
		exit(EXIT_FAILURE);
	}

	valread = read(new_socket, buffer, 1024);
	std::cout << "msg from client: " << buffer << '\n';
	send(new_socket, hello, strlen(hello), 0);
	std::cout << "Hello message sent\n";
	// closing the connected socket
	close(new_socket);
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
	return 0;
}
