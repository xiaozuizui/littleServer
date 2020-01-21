#pragma once
#include "TCPSocket.h"

class SocketUtil
{
public:
	static TCPSocketPtr CreateTCPSocket(SOCKET inSocket);
	
};