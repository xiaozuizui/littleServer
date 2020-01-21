#include "SocketUtil.h"

TCPSocketPtr SocketUtil::CreateTCPSocket(int inSocket)
{
	return TCPSocketPtr(new TCPSocket(inSocket));
}
