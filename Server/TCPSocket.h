#pragma once


#include <cstdint>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <memory>
#include <arpa/inet.h>


#ifdef LINUX
#define SOCKET int
#else
#define SOCKET int
#endif

//struct in_addr
//{
//	union
//	{
//		struct
//		{
//			uint8_t s_b1, s_b2, s_b3, s_b4;
//		}S_un_b;;
//		struct
//		{
//			uint16_t s_w1, s_w2;
//		}S_un_w;;
//
//		uint32_t S_addr;
//	};	
//};



//类型安全的address
class SocketAddress
{
public:
	SocketAddress(const char* ip,int port)
	{
		GetAsSockAddrIn()->sin_family = AF_INET;
		GetAsSockAddrIn()->sin_addr.s_addr = inet_addr(ip);
		GetAsSockAddrIn()->sin_port = htons(port);
	}

	SocketAddress(uint32_t indAdress,uint16_t inPort)
	{
		GetAsSockAddrIn()->sin_family = AF_INET;
		GetAsSockAddrIn()->sin_addr.s_addr = indAdress;
		GetAsSockAddrIn()->sin_port = inPort;
	}

	SocketAddress(const sockaddr& inSockAddr)
	{
		memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
	}

	socklen_t GetSize() const { return sizeof(sockaddr); }

protected:
	friend class TCPSocket;
	sockaddr mSockAddr;

	sockaddr_in* GetAsSockAddrIn()
	{
		return reinterpret_cast<sockaddr_in*>(&mSockAddr);
	}
};

typedef std::shared_ptr<SocketAddress> SocketAddressPtr;



class TCPSocket
{
public:
	~TCPSocket(){};
	int Connect(const SocketAddress& inAddress);
	int Bind(const SocketAddress& inToAddress);
	int Listen(int BackLog = 32);
	std::shared_ptr<TCPSocket> Accpet(SocketAddress& inFromAddress);
	int Send(const void* inData, int length);
	int Receive(void* inBuff, int inLen);
	SOCKET mSocket;

private:
	friend class SocketUtil;
	TCPSocket(SOCKET insocket) : mSocket(insocket) {};
	
};


typedef std::shared_ptr<TCPSocket> TCPSocketPtr;