//
// Created by loadstar on 2021/9/11.
//

#include <netinet/in.h>

#include "../StreamSocket.h"

StreamSocket::StreamSocket(Reactor& reactor)
: reactor_(reactor) {
    fd_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd_ < 0) {
        throw std::system_error(errno, std::system_category());
    }
    makeNoBlock(fd_);
    reactor_.add(fd_);

}

StreamSocket::StreamSocket(Reactor& reactor, int fd)
: reactor_(reactor){
    fd_ = fd;
    reactor_.add(fd_);
}

void StreamSocket::bind(short port) const {
    ::sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (::bind(fd_, (sockaddr*)(&addr), sizeof(addr)) < 0) {
        throw std::system_error(errno, std::system_category());
    }
}

void StreamSocket::listen() {
    if (::listen(fd_, 1024) < 0) {
        throw std::system_error(errno, std::system_category());
    }
}

void StreamSocket::read(Buffer buffer, ReadCompleteHandler handler) {
    reactor_.registerRead(std::make_shared<ReadFullHandler>(fd_, reactor_, buffer, handler));
}


void StreamSocket::write(Buffer buffer, WriteCompleteHandler handler) {
    reactor_.registerWrite(std::make_shared<WriteFullHandler>(fd_, reactor_, buffer, handler));
}

int StreamSocket::fd() const {
    return fd_;
}



