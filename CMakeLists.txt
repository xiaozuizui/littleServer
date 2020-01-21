# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

add_definitions("-DDEBUG")


MESSAGE(STATUS "operation system is ${CMAKE_HOST_SYSTEM_NAME}") 
IF(CMAKE_HOST_SYSTEM_NAME MATCHES "Linux")	
	MESSAGE(STATUS "current platform: Linux ")
	add_definitions("-DLINUX")
ELSEIF (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")	
	MESSAGE(STATUS "current platform: Windows")
ELSEIF (CMAKE_HOST_SYSTEM_NAME MATCHES "FreeBSD")	
	MESSAGE(STATUS "current platform: FreeBSD")
ELSE ()	
	MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF ()
MESSAGE(STSTUS "###################################")



project ("Server")

# 包含子项目。
add_subdirectory ("Server")

find_package(protobuf)
if(NOT protobuf_FOUND)
	message("Can't find protobuf")
	# 包含的cmakelist自动添加头文件
	add_subdirectory ("protobuf-3.11.1/cmake")
else()
	
	message("Find protobuf")
endif()

#add_subdirectory("SampleClient")