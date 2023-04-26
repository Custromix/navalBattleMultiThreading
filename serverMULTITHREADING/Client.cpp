#include "Utils.h"

Client::Client()
{
}

Client::Client(SOCKET* clientSocket, sockaddr_in* clientAddr)
{
	clientSocket_ = clientSocket;
	clientAddr_ = clientAddr;
	clientAddrSize_ = sizeof(clientAddr_);
}

Client::~Client()
{
}

void Client::SetSockAddr(sockaddr_in* sockAddr)
{
	clientAddr_ = sockAddr;
	clientAddrSize_ = sizeof(clientAddr_);
}
