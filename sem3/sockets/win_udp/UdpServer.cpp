#include<winsock2.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data

void handleError(bool err, const char* msg)
{
	if (!err)
		return;
	std::cout << msg << WSAGetLastError();
	exit(EXIT_FAILURE);
}

int main()
{
	char buf[BUFLEN];

	//Initialize winsock
	std::cout << "Initialising Winsock...\n";
	WSADATA wsa;
	int res = WSAStartup(MAKEWORD(2, 2), &wsa);
	handleError(res != 0, "Failed. Error Code : ");

	std::cout << "Initialized.\n";

	//Create a socket
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	handleError(sock == SOCKET_ERROR, "Could not create socket : ");

	std::cout << "Socket created.\n";

	//Prepare the sockaddr_in structure
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(PORT);

	//Bind
	res = bind(sock, (struct sockaddr*)&server, sizeof(server));
	handleError(res == SOCKET_ERROR, "Bind failed with error code : ");
	std::cout << "Bind done\n";

	sockaddr_in si_other;
	int slen;
	//keep listening for data
	while (1)
	{
		std::cout << "Waiting for data...\n";

		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);

		int recv_len;
		//try to receive some data, this is a blocking call
		if ((recv_len = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen)) == SOCKET_ERROR)
		{
			printf("recvfrom() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}

		//print details of the client/peer and the data received
		//printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
		printf("Data: %s\n", buf);

		//now reply the client with the same data
		if (sendto(sock, buf, recv_len, 0, (struct sockaddr*)&si_other, slen) == SOCKET_ERROR)
		{
			printf("sendto() failed with error code : %d", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	closesocket(sock);
	WSACleanup();

	return 0;
}