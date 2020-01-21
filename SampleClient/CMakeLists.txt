


set(client_headers 
../Server/epoll.h
../Server/TCPSocket.h
../Server/SocketUtil.h
../Server/GameObject.h
../Server/MemoryBitStream.h
../Server/ReplicationManager.h
)

set(client_files
client.cpp
../Server/epoll.cpp
../Server/TCPSocket.cpp
../Server/SocketUtil.cpp
../Server/GameObject.cpp
../Server/MemoryBitStream.cpp
../Server/ReplicationManager.cpp
)




add_executable (SampleClient ${client_headers} ${client_files})
target_link_libraries(SampleClient PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)