// TestChat.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <thread>
#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#pragma comment(lib, "Ws2_32.lib")

/*
SOCKET Make_Socket()
{
	
}

*/



void recv_data(int Result , SOCKET AcceptSocket, char buffer[])
{
	while (true)
	{
		Result = recv(AcceptSocket, buffer, 512, 0);
		if (Result > 0)
		{
			printf("Bytes received: %d\n", Result);
			printf("%.*s", (int)Result, buffer);
			
		}
		

	}
}
int main()
{
	WSADATA wsaData;
	SOCKET ListenSocket = INVALID_SOCKET;
	sockaddr_in service;
	int Result = 0;
	

	char buffer[512];
	
	char testbuffer[512] = "Get Message";
	

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



	
	SOCKET arr_AcceptSocket[10];
	int connectcount = 0;
	sockaddr_in clients_addr[10];

	struct sockaddr_in client_addr;


	socklen_t slen = sizeof(client_addr);
	SOCKET AcceptSocket;
	wprintf(L"Waiting for client to connect...\n");
	
	//쓰레드로 변경 필요
	while (1)
	{
		arr_AcceptSocket[connectcount] = accept(ListenSocket, (SOCKADDR *)&clients_addr[connectcount], &slen);
		if (arr_AcceptSocket[connectcount] == INVALID_SOCKET) {
			wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
			closesocket(ListenSocket);
			WSACleanup();

			return 1;
		}
		else
		{
			wprintf(L"Client connected.\n");
			wprintf(L"%d user", connectcount);
			connectcount++;
		}
	

	/*
	AcceptSocket = accept(ListenSocket, ( SOCKADDR *)&client_addr, &slen);
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
	

	/*
	std::thread th1(recv_data, Result, AcceptSocket, buffer);
	th1.join();
	

	while (true)
	{
		Result = recv(AcceptSocket, buffer, 512, 0);
		if (Result > 0)
		{
			printf("Bytes received: %d\n", Result);
			printf("%.*s", (int)Result, buffer);
			
			send(AcceptSocket, testbuffer, 512, 0);
		}

	}
	*/
		for (int i = 0; i < connectcount; i++)
		{
			Result = recv(arr_AcceptSocket[connectcount], buffer, 512, 0);
			if (Result > 0)
			{
				printf("Bytes received: %d\n", Result);
				printf("%.*s", (int)Result, buffer);

				send(arr_AcceptSocket[connectcount], testbuffer, 512, 0);
			}
		}
	}
}

