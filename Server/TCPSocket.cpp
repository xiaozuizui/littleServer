#include "TCPSocket.h"

#define NO_ERROR 0


int TCPSocket::Connect(const SocketAddress& inAddress)
{
	int error = connect(mSocket, &inAddress.mSockAddr, inAddress.GetSize());
	if(error < 0 )
	{
		//error 
	}

	return NO_ERROR;
}

int TCPSocket::Listen(int inBackLog)
{
	int error =listen(mSocket, inBackLog);
	if(error < 0)
	{
		//error
	}
	return NO_ERROR;
}

std::shared_ptr<TCPSocket> TCPSocket::Accpet(SocketAddress& inFromAddress)
{
	socklen_t length = inFromAddress.GetSize();
	SOCKET newSocket = accept(mSocket, &inFromAddress.mSockAddr, &length);
	if(newSocket <0 )
	{
		//error
	}

	return TCPSocketPtr(new TCPSocket(newSocket));
}

int TCPSocket::Send(const void* inData, int length)
{
	const int bytesSentCount = send(mSocket, static_cast<const char*>(inData), length, 0);
	if(bytesSentCount < 0 )
	{
		//error
	}
	return bytesSentCount;
}

int TCPSocket::Receive(void* inBuff, int inLen)
{
	const int byteReceivedCount = recv(mSocket, static_cast<char*>(inBuff), inLen, 0);
	if(byteReceivedCount < 0 )
	{
		//error
	}
	return byteReceivedCount;
}


int TCPSocket::Bind(const SocketAddress& inToAddress)
{
	if (bind(mSocket, (struct sockaddr*) & inToAddress.mSockAddr, inToAddress.GetSize()) < 0) {
		//error
		perror("bind()");
		exit(2);
	}
	return 1;
}
