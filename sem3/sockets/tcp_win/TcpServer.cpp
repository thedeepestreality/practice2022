// Server side C/C++ program to demonstrate Socket
// programming
#include<winsock2.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
const int PORT = 2024;

void handleError(bool err, const char* msg)
{
	if (!err)
		return;
	std::cout << msg << WSAGetLastError();
	exit(EXIT_FAILURE);
}

int main(int argc, char const* argv[])
{
	//Initialize winsock
	std::cout << "Initialising Winsock...\n";
	WSADATA wsa;
	int res = WSAStartup(MAKEWORD(2, 2), &wsa);
	handleError(res != 0, "Failed. Error Code : ");

	int valread;
	int opt = 1;
	const char* hello = "hello";
	char buffer[1024] = { 0 };
	SOCKET server_sock = socket(AF_INET, SOCK_STREAM, 0);
	// Creating socket file descriptor
	handleError(server_sock == SOCKET_ERROR, "Could not create socket : ");

	std::cout << "Server socket created.\n";

	struct sockaddr_in address;
	int addrlen = sizeof(address);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(PORT);

	// Forcefully attaching socket to the port 8080
	res = bind(
		server_sock,
		(struct sockaddr*)&address,
		sizeof(address)
	);
	handleError(res == SOCKET_ERROR, "Bind failed with error code : ");
	std::cout << "Bind done\n";

	res = listen(server_sock, 3);
	if (res < 0) {
		perror("listen");
		exit(EXIT_FAILURE);
	}

	SOCKET new_socket = accept(
		server_sock,
		(struct sockaddr*)&address,
		&addrlen
	);
	handleError(new_socket == SOCKET_ERROR, "Accept failed with error code : ");
	std::cout << "Accepted\n";

	valread = recv(new_socket, buffer, 1024, 0);
	std::cout << "msg from client: " << buffer << '\n';
	send(new_socket, hello, strlen(hello), 0);
	std::cout << "Hello message sent\n";
	// closing the connected socket
	closesocket(new_socket);
	// closing the listening socket
	closesocket(server_sock);
	WSACleanup();
	return 0;
}
