//
// Created by loadstar on 2021/9/20.
//

#include "../ListenSocket.h"

#include <utility>

ListenSocket::ListenSocket(Reactor &reactor)
:reactor_(reactor){
    fd_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd_ < 0) {
        throw std::system_error(errno, std::system_category());
    }
    makeNoBlock(fd_);
    reactor_.add(fd_);
}

void ListenSocket::bind(short port) const {
    ::sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (::bind(fd_, (sockaddr*)(&addr), sizeof(addr)) < 0) {
        throw std::system_error(errno, std::system_category());
    }
}

void ListenSocket::listen() const {
    if (::listen(fd_, 1024) < 0) {
        throw std::system_error(errno, std::system_category());
    }
}

void ListenSocket::accept(AcceptCompleteHandler handler) {
    reactor_.registerRead(fd_, AcceptHandler(reactor_, fd_, std::move(handler)));
}
