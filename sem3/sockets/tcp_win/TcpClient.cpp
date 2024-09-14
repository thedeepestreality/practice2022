#include<winsock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <tchar.h>

const int PORT = 2024;
#pragma comment(lib,"ws2_32.lib") //Winsock Library

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

	const char* hello = "Hello from client";
	char buffer[1024] = { 0 };
	SOCKET client_sock = socket(AF_INET, SOCK_STREAM, 0);
	handleError(client_sock == SOCKET_ERROR, "Could not create socket : ");


	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	//servaddr.sin_addr.s_addr = INADDR_ANY;
	InetPton(AF_INET, _T("127.0.0.1"), &servaddr.sin_addr.s_addr);

	int status = connect(
		client_sock,
		(struct sockaddr*)&servaddr,
		sizeof(servaddr)
	);
	handleError(status == SOCKET_ERROR, "Could not create socket : ");

	send(client_sock, hello, strlen(hello), 0);
	std::cout << "Hello message sent\n";
	int valread = recv(client_sock, buffer, 1024, 0);
	std::cout << "Message from server: " << buffer << '\n';

	// closing the connected socket
	closesocket(client_sock);
	WSACleanup();
	return 0;
}
