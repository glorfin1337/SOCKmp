#pragma once

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

#pragma comment (lib, "Ws2_32.lib")

class Server
{
public:
	// Variables
	int connection = 0;
	
	// Functions
	int CreateServer(PCSTR port);
	int StartListening(int sock, addrinfo* result);
	int CloseServer(int sock);

	// Callbacks
	int OnDataRecieve(int sock, int recvlen, char dRecieved);
};