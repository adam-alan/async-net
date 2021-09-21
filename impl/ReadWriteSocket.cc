//
// Created by loadstar on 2021/9/11.
//

#include <netinet/in.h>

#include "../ReadWriteSocket.h"

ReadWriteSocket::ReadWriteSocket(Reactor& reactor)
: reactor_(reactor) {
    fd_ = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fd_ < 0) {
        throw std::system_error(errno, std::system_category());
    }
    makeNoBlock(fd_);
    reactor_.add(fd_);

}

ReadWriteSocket::ReadWriteSocket(Reactor& reactor, int fd)
: reactor_(reactor){
    fd_ = fd;
    reactor_.add(fd_);
}

void ReadWriteSocket::bind(short port) const {
    ::sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (::bind(fd_, (sockaddr*)(&addr), sizeof(addr)) < 0) {
        throw std::system_error(errno, std::system_category());
    }
}

void ReadWriteSocket::listen() {
    if (::listen(fd_, 1024) < 0) {
        throw std::system_error(errno, std::system_category());
    }
}

void ReadWriteSocket::read(Buffer buffer, const ReadWriteCompleteHandler& handler) {

    reactor_.registerRead(fd_, ReadFullHandler(reactor_, fd_, buffer, handler));
}


void ReadWriteSocket::write(Buffer buffer, const ReadWriteCompleteHandler& handler) {
    reactor_.registerRead(fd_, WriteFullHandler(reactor_, fd_, buffer, handler));
}



