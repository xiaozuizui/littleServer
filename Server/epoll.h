#pragma once

#include "TCPSocket.h"

#define EVENT_MAX 1024


/* �¼��������ֵ */
#define MAX_EVENTS 256


/* Ϊÿһ���ͻ��˶�̬����fd_buf_t �ṹ�� */
static void* new_fd_buf(int fd);



/* ��ȡһ���������ӵ�sockfd */
TCPSocketPtr run_getsockfd(const char* ip, int port);

/* ִ��epoll�߼� (��������Ӽ����¼����ȴ�����)*/
void run_epoll(TCPSocketPtr listen, int listen_sockfd);

/* ����ͻ����¼����� */
void run_action(int epollfd, int index);

/* ����ͻ����������󣬲���ӵ�epollģ���� */
void run_accept(int epollfd, TCPSocketPtr listen,int listen_sockfd);
