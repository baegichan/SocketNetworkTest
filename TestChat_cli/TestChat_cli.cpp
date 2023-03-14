// TestChat_cli.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")
#include <iostream>

int main()
{
	char recvbuf[512] = "";
	char sendbuf[512] = "test Message \n";
	int recvbuflen = 512;
	//----------------------
   // Initialize Winsock
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR) {
		wprintf(L"WSAStartup function failed with error: %d\n", iResult);
		return 1;
	}
	//----------------------
	// Create a SOCKET for connecting to server
	SOCKET ConnectSocket;
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET) {
		wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
		//WSACleanup();
		return 1;
	}

	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &clientService.sin_addr);
	clientService.sin_port = htons(8889);

	//----------------------
	// Connect to server.
	iResult = connect(ConnectSocket, (SOCKADDR *)& clientService, sizeof(clientService));
	if (iResult == SOCKET_ERROR) {
		wprintf(L"connect function failed with error: %ld\n", WSAGetLastError());
		iResult = closesocket(ConnectSocket);
		if (iResult == SOCKET_ERROR)
			wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	wprintf(L"Connected to server.\n");

	//iResult = closesocket(ConnectSocket);
	if (iResult == SOCKET_ERROR) {
		wprintf(L"closesocket function failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	for (int i = 0; i < 10; i++)
	{
		iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
	}
	
	if (iResult == SOCKET_ERROR) {
		wprintf(L"send failed with error: %d\n", WSAGetLastError());
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	do {

		iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0)
			wprintf(L"Bytes received: %d\n", iResult);
		else if (iResult == 0)
			wprintf(L"Connection closed\n");
		else
			wprintf(L"recv failed with error: %d\n", WSAGetLastError());

	} while (1);
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
