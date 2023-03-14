// TestChat.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN


#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

int main()
{
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
	sockaddr_in service;
	int Result = 0;
	

	char buffer[512];
	

	WSAStartup(MAKEWORD(2,2),&wsaData);
	
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (ListenSocket == INVALID_SOCKET)
	{
		std::cout << "INVALID SOCKET";
	}
	else
	{
		std::cout << "VALID SOCKET";
	}
	
	service.sin_family = AF_INET;
	//service.sin_addr.s_addr = inet_addr("127.0.0.1");
	inet_pton(AF_INET,  "127.0.0.1", &service.sin_addr);
	service.sin_port = htons(8889);

	Result = bind(ListenSocket, (SOCKADDR *)& service, sizeof(service));
	if (Result == SOCKET_ERROR)
	{
		std:: cout << "ERROR";
		WSACleanup();
		return 1;
	}
	
	if (listen(ListenSocket, 1) == SOCKET_ERROR)
	{
		std::cout << WSAGetLastError();
	}







	SOCKET AcceptSocket;
	wprintf(L"Waiting for client to connect...\n");

	//----------------------
	// Accept the connection.
	AcceptSocket = accept(ListenSocket, NULL, NULL);
	if (AcceptSocket == INVALID_SOCKET) {
		wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else 
	{
		wprintf(L"Client connected.\n");
	}

	while (true)
	{
			Result = recv(AcceptSocket, buffer, 512, 0);
			if (Result > 0)
			{
				printf("Bytes received: %d\n", Result);
				printf("%.*s", (int)Result, buffer);
			}
		

	}
	// No longer need server socket
}

