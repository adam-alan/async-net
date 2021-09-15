cmake_minimum_required(VERSION 3.20)
project(async_net)

set(CMAKE_CXX_STANDARD 20)

add_executable(async_net main.cpp impl/StreamSocket.cc StreamSocket.h FdUtils.h detail/AcceptHandler.h impl/Acceptor.cc Acceptor.h detail/impl/ConnectHandler.cc detail/ConnectHandler.h impl/Buffer.cc impl/FdUtils.cc Reactor.h impl/Reactor.cc detail/EpollWrapper.h detail/impl/EpollWrapper.cc detail/impl/AcceptHandler.cc)
