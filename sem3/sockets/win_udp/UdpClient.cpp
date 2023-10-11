/*
	Simple udp client
*/
#include <winsock2.h>
#include <iostream>
#include <WS2tcpip.h>
#include <tchar.h>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"	//ip address of udp server
#define BUFLEN 512	//Max length of buffer
#define PORT 8888	//The port on which to listen for incoming data

void handleError(bool err, const char* msg)
{
	if (!err)
		return;
	std::cout << msg << WSAGetLastError();
	exit(EXIT_FAILURE);
}

int main(void)
{
	char buf[BUFLEN];
	char message[BUFLEN];
	
	//Initialize winsock
	std::cout << "\nInitializing Winsock...\n";
	WSADATA wsa;
	int res = WSAStartup(MAKEWORD(2, 2), &wsa);
	handleError(res != 0, "Failed. Error Code : ");

	std::cout << "Initialized.\n";

	//create socket
	int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	handleError(sock == SOCKET_ERROR, "socket() failed with error code : ");

	//setup address structure
	sockaddr_in si_other;
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	InetPton(AF_INET, _T(SERVER), &si_other.sin_addr.s_addr);
	int slen = sizeof(si_other);

	//start communication
	while (1)
	{
		std::cout << "Enter message : \n";
		std::cin >> message;

		//send the message
		res = sendto(sock, message, strlen(message), 0, (sockaddr*)&si_other, slen);
		handleError(res == SOCKET_ERROR, "sendto() failed with error code : ");

		//receive a reply and print it
		//clear the buffer by filling null, it might have previously received data
		memset(buf, '\0', BUFLEN);
		//try to receive some data, this is a blocking call
		res = recvfrom(sock, buf, BUFLEN, 0, (struct sockaddr*)&si_other, &slen);
		handleError(res == SOCKET_ERROR, "recvfrom() failed with error code : ");

		std::cout << buf;
	}

	closesocket(sock);
	WSACleanup();

	return 0;
}