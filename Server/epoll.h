#pragma once

#include "TCPSocket.h"

#define EVENT_MAX 1024


/* 事件数组最大值 */
#define MAX_EVENTS 256


/* 为每一个客户端动态分配fd_buf_t 结构体 */
static void* new_fd_buf(int fd);



/* 获取一个监听连接的sockfd */
TCPSocketPtr run_getsockfd(const char* ip, int port);

/* 执行epoll逻辑 (创建，添加监听事件，等待返回)*/
void run_epoll(TCPSocketPtr listen, int listen_sockfd);

/* 处理客户端事件就绪 */
void run_action(int epollfd, int index);

/* 处理客户端连接请求，并添加到epoll模型中 */
void run_accept(int epollfd, TCPSocketPtr listen,int listen_sockfd);
