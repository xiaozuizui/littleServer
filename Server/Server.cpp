// Server.cpp: 定义应用程序的入口点。
//
#include <iostream>
#include <fstream>
#include <string>

#include "Server.h"
#include "GameObject.h"
#include "ReplicationManager.h"


using namespace std;
#define EPOLL

int main(int argc, char** argv)
{
	//GOOGLE_PROTOBUF_VERIFY_VERSION;
	/*tutorial::AddressBook address_book;
	tutorial::Person p;
	p.set_name("littlemm");
	p.set_id(123222);
	cout << p.id() << endl;
	char outname[] = { "test" };
	fstream output(outname, ios::out | ios::trunc | ios::binary);
	if (!p.SerializeToOstream(&output)) {
		cerr << "Failed to write address book." << endl;
		return -1;
	}
	cout << "Hello CMake." << endl;
	return 0;*/

	//tutorial::Person person;
	//person.set_email("12@qwe");
	//

	auto link = &(LinkingContext::getInstance());

	ObjectCreationRegistry::getInstance().RegisterCreationFunction<Person>();
	Person* p =  static_cast<Person*>(ObjectCreationRegistry::getInstance().CreateGameObject('PERS'));

	p->Set_x(1.0f);
	p->Set_y(2.0f);
	p->Set_z(3.0f);

	
	OutputMemoryBitStream o;
	p->WriteToBitStream(o);

	char* des;
	des = static_cast<char*>(std::malloc(12));
	std::memcpy(des, o.GetBytePtr(), 12);


	//收到的bit流
	InputMemoryBitStream i(des,12);

	/*
	 * 处理字节流，反序列化，更新世界
	 * 
	 */
	
	//
	//char* d = std::realloc(d,o.)
	//memccpy(d,) 
	Person n;
	n.ReadFromBitStream(i);




	
	//

#ifdef EPOLL

	/* 使用格式 ./xxx  服务器ip  服务器端口 */
	if (argc != 3)
	{
		printf("usage: [server_ip] [server_port]\n");
		return 1;
	}

	/* 获取监听socketfd  */
	TCPSocketPtr listen_sockfd = run_getsockfd(argv[1], atoi(argv[2]));

	/* 执行epoll 逻辑 */
	run_epoll(listen_sockfd, listen_sockfd->mSocket);
#endif

}
