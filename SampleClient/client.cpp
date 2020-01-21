



#include <cstdio>
#include "../Server/GameObject.h"
#include "../Server/ReplicationManager.h"
#include "../Server/TCPSocket.h"
#include "../Server/SocketUtil.h"

int main()
{


	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket()");
		exit(1);
	}
		/* ¸´ÓÃ*/
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	SocketAddressPtr server_ = SocketAddressPtr(new SocketAddress("127.0.0.1", 9999));
	auto connSocket = SocketUtil::CreateTCPSocket(sock);
	connSocket->Connect(*server_);

	const char* testMsg = { "qwe" };
	connSocket->Send(testMsg,3);

	ReplicationManager replication_manager;
	Person p;

	p.Set_x(10.0);
	p.Set_y(20.0);
	p.Set_z(30.0);

	

	printf("new");
}