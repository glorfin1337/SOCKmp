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
	bool connection = false;
	
	// Functions
	int CreateConnection(PCSTR port);
	int StartListening(int sock, addrinfo* result);
	int CloseConnection(int sock);

	// Callbacks
	int OnDataRecieve(int sock, int recvlen, char* dRecieved);
};