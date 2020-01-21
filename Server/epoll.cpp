#include "epoll.h"

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h> 
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <cstdio>
#include <iostream>

#include "TCPSocket.h"
#include "testpb.h"
#include "SocketUtil.h"



/* ÿһ���ͻ������¼����� events.data.ptr ��ָ������� */
typedef struct fd_buf
{
	int  fd;        /* ���浱ǰ�ͻ��˵�socket������ */
	char buf[1024]; /* ��ǰ�ͻ��˵Ļ����� */
}fd_buf_t, * fd_buf_p;



/* epoll�¼��� */
struct epoll_event evts[MAX_EVENTS];



/* ��ȡһ������socket */
TCPSocketPtr run_getsockfd(const char* ip, int port)
{
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket()");
		exit(1);
	}

	/* ����*/
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	/*struct sockaddr_in server;
	bzero(&server, sizeof(server));
	server.sin_addr.s_addr = inet_addr(ip);
	server.sin_port = htons(port);
	server.sin_family = AF_INET;*/

	SocketAddressPtr server_ = SocketAddressPtr( new SocketAddress("127.0.0.1",9999));
	//bind(sock,(struct  sockaddr*) server_)
	auto ListenSocket = SocketUtil::CreateTCPSocket(sock);
	ListenSocket->Bind(*server_);
	ListenSocket->Listen();
	int count = server_.use_count();

	/*if (bind(sock, (struct sockaddr*) & server, sizeof(server)) < 0) {
		perror("bind()");
		exit(2);
	}

	if (listen(sock, 5) < 0) {
		perror("listen()");
		exit(3);
	}*/
	return ListenSocket;
}


/* ִ��epoll�߼� (��������Ӽ����¼����ȴ�����)*/
void run_epoll(TCPSocketPtr listen,  int listen_sockfd)
{
	// 1. ���� epoll ģ��
	int epollfd = epoll_create(256);
	if (epollfd < 0)
	{
		perror("epoll_create()");
		exit(4);
	}

	// 2. ��Ӽ�����������ģ���У������Ķ��¼�
	struct epoll_event evt;
	evt.events = EPOLLIN;
	evt.data.ptr = new_fd_buf(listen_sockfd);
	// epollcreate����ֵ
	// ������EPOLL_CTL_ADD ע���µ�fd��epfd�� EPOLL_CTL_MOD/DEL
	// ��Ҫ������fd
	// ��Ҫ�������¼�
	epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sockfd, &evt);

	int nfds = 0;        /* �����¼����� */
	int timeout = 1000;  /* һ�볬ʱ  */
	while (1)
	{
		//evts���ں˵õ��¼�����
		nfds = epoll_wait(epollfd, evts, MAX_EVENTS, timeout);
		if (nfds < 0)
		{
			perror("epoll_wait()");
			continue;
		}
		else if (nfds == 0)
		{
			printf("epoll_wait() timeout\n");
		}
		else
		{
			/* ���������Ѿ��������¼� */
			int idx_check = 0;
			for (; idx_check < nfds; idx_check++)
			{
				fd_buf_p fp = reinterpret_cast<fd_buf_p>(evts[idx_check].data.ptr);
				/* ����socket ���¼����� */
				if (fp->fd == listen_sockfd && \
					evts[idx_check].events & EPOLLIN)
				{
					/* ���ܿͻ��˵����� */
					run_accept(epollfd, listen,listen_sockfd);
				}/* �ͻ���socket �¼����� */
				else if (fp->fd != listen_sockfd)
				{
					run_action(epollfd, idx_check);
				}
			}
		}
	}
}

static void* new_fd_buf(int fd)
{
	fd_buf_p ret = (fd_buf_p)malloc(sizeof(fd_buf_t));
	assert(ret != NULL);

	ret->fd = fd;
	memset(ret->buf, 0, sizeof(ret->buf));
	return ret;
}

/* ����ͻ����������󣬲���ӵ�epollģ���� */
void run_accept(int epollfd, TCPSocketPtr listen,int listen_sockfd)
{

	//struct sockaddr_in cliaddr;
	//socklen_t clilen = sizeof(cliaddr);

	SocketAddressPtr cliaddr;
	int count = listen.use_count();
	int new_sock = listen->Accpet(*cliaddr.get())->mSocket;

	//int new_sock = accept(listen_sockfd, (struct sockaddr*) & cliaddr, &clilen);
	if (new_sock < 0)
	{
		perror("accept");
		return;
	}


	//printf("connect succed: ip %s port %d \n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));

	/* ����ͻ������ӵ�sockfd ��ӵ�epollģ���У������Ķ��¼� */
	struct epoll_event evt;
	evt.events = EPOLLIN;
	evt.data.ptr = new_fd_buf(new_sock); /* Ϊÿһ���ͻ������ӷ���fd�ͻ����� */
	epoll_ctl(epollfd, EPOLL_CTL_ADD, new_sock, &evt);
}

/* ����ͻ����¼����� */
void run_action(int epollfd, int index)
{

	/* ȡ�ÿͻ��˽ṹ������ָ�� */
	fd_buf_p fdp = reinterpret_cast<fd_buf_p>(evts[index].data.ptr);

	/* ���¼����� */
	if (evts[index].events & EPOLLIN)
	{
		ssize_t s = read(fdp->fd, fdp->buf, sizeof(fdp->buf));
		if (s > 0)
		{
			fdp->buf[s] = 0;
			printf("client request:\n");
			//printf("\n %s \n", fdp->buf);

			//protobuf

			tutorial::Person p;
			p.ParseFromArray(fdp->buf, s);

			//printf("\nperson name: %s \n", p.name());

			std::cout << "\n person name " << p.name() << std::endl;
			//protobuf

			struct epoll_event evt;
			evt.events = EPOLLOUT;
			evt.data.ptr = fdp;
			epoll_ctl(epollfd, EPOLL_CTL_MOD, fdp->fd, &evt);
		}
		else if (s <= 0)
		{
			/* �ǵùر�socket����epoll ģ����ɾ����㲢�ͷŷ�����ڴ� */
			std::cout << ("\nclient exit!\n");
			close(fdp->fd);
			epoll_ctl(epollfd, EPOLL_CTL_DEL, fdp->fd, NULL);
			free(fdp);
		}
	}
	else if (evts[index].events & EPOLLOUT)
	{/* д�¼����� */
		/* ������Ϻ󣬼ǵ���������� */
		const char* msg = "HTTP/1.1 200 OK\r\n\r\n<html><h1>littlemm!</h1></html>";
		write(fdp->fd, msg, strlen(msg));

		struct epoll_event evt;
		evt.events = EPOLLIN;
		evt.data.ptr = fdp;
		epoll_ctl(epollfd, EPOLL_CTL_MOD, fdp->fd, &evt);

		//close(fdp->fd);
		//epoll_ctl(epollfd, EPOLL_CTL_DEL, fdp->fd, NULL);
		//free(fdp);
	}
}
