native CreateConnection(port[]);
native CloseConnection(sock);

forward OnDataRecieve(sock, recvlen, recvbuf[]);