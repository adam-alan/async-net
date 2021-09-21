cmake_minimum_required(VERSION 3.20)
project(async_net)

set(CMAKE_CXX_STANDARD 20)

add_executable(async_net main.cpp impl/ReadWriteSocket.cc ReadWriteSocket.h detail/FdUtils.h detail/AcceptHandler.h impl/Acceptor.cc Acceptor.h detail/impl/ConnectHandler.cc detail/ConnectHandler.h impl/Buffer.cc impl/FdUtils.cc Reactor.h impl/Reactor.cc detail/EpollWrapper.h detail/impl/EpollWrapper.cc detail/impl/AcceptHandler.cc impl/ListenSocket.cc ListenSocket.h detail/ReadUntilHandler.h detail/impl/ReadWriteFullHandler.cc detail/ReadWriteFullHandler.h detail/impl/WriteFullHandler.cc detail/ReadFullHandler.cc)
