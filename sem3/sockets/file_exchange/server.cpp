// Server side C/C++ program to demonstrate Socket
// programming
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <iostream>
#include <sstream>
#include <nlohmann/json.hpp>

// for convenience
using json = nlohmann::json;

const int PORT = 2024;

int main(int argc, char const* argv[])
{
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	// Creating socket file descriptor
	if (server_fd < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
    int opt = 1;
	// Forcefully attaching socket to the port 8080
    int res = setsockopt(
        server_fd, 
        SOL_SOCKET,
		SO_REUSEADDR | SO_REUSEPORT, 
        &opt,
		sizeof(opt)
    );
	if (res < 0) {
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
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

	std::cout << "[server] Server started!\n";

	while (true)
	{
		int sender_socket = accept(
			server_fd, 
			(struct sockaddr*)&address,
			(socklen_t*)&addrlen
		);
		if (sender_socket < 0) {
			perror("accept");
			exit(EXIT_FAILURE);
		}
        std::cout << "[server] sender socket connected\n";

        // int receiver_socket = accept(
		// 	server_fd, 
		// 	(struct sockaddr*)&address,
		// 	(socklen_t*)&addrlen
		// );
		// if (receiver_socket < 0) {
		// 	perror("accept");
		// 	exit(EXIT_FAILURE);
		// }
        // std::cout << "[server] receiver socket connected\n";

        char sender_request[] = "send";
        send(sender_socket, sender_request, sizeof(sender_request), 0);

        std::cout << "[server] sender request was sent\n";

		char buffer[50000];
        int valread = read(sender_socket, buffer, 512);
		json obj = json::parse(buffer);

		std::cout << "[server] sender sent json: \n";
		for (auto const& file: obj["files"])
			std::cout << file << '\n';

        valread = read(sender_socket, buffer, 4);
        int sz = *(int*)buffer;
        std::cout << "[server] sender sent " << sz << "bytes \n";

		valread = read(sender_socket, buffer+4, sz);
        std::cout << "[server] file was accepted\n";

		// send(receiver_socket, buffer, sz+4, 0);
		// std::cout << "[server] sender data was sent to receiver\n";
		// closing the connected socket
		close(sender_socket);
        // close(receiver_socket);
	}
	// closing the listening socket
	shutdown(server_fd, SHUT_RDWR);
    close(server_fd);
	return 0;
}
