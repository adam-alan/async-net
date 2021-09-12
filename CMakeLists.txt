cmake_minimum_required(VERSION 3.20)
project(async_net)

set(CMAKE_CXX_STANDARD 20)

add_executable(async_net main.cpp StreamSocket.cc StreamSocket.h SocketUtils.h AcceptEvent.h Acceptor.cc Acceptor.h ConnectEvent.cc ConnectEvent.h Buffer.cc SocketUtils.cc Reactor.h Reactor.cc EpollWrapper.h EpollWrapper.cc AcceptEvent.cc)
