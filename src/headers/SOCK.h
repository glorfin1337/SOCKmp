#pragma once

class Server
{
public:
	int connection = 0;

	int CreateServer();
	int ReadData(int sock);
	int CloseServer(int sock);
};