# CMakeList.txt: Server 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

# 将源代码添加到此项目的可执行文件。




set(server_headers 
Server.h
epoll.h
testpb.h
TCPSocket.h
SocketUtil.h
GameObject.h
)

set(server_files
Server.cpp
epoll.cpp
testpb.cc
TCPSocket.cpp
SocketUtil.cpp
GameObject.cpp
)




add_executable (Server ${server_headers} ${server_files})
target_link_libraries(Server PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite)
#add_dependencies(protobuf)

#get_cmake_property(_variableNames VARIABLES)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()