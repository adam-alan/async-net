//
// Created by loadstar on 2021/9/11.
//

#include <netinet/in.h>

#include "StreamSocket.h"

void StreamSocket::bind(short port) const {
    ::sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (::bind(socketEventData_.fd, (sockaddr*)(&addr), sizeof(addr)) < 0) {
        throw std::system_error(errno, std::system_category());
    }
}

void StreamSocket::listen() {
    if (::listen(socketEventData_.fd, 1024) < 0) {
        throw std::system_error(errno, std::system_category());
    }
}

void StreamSocket::read(Buffer buffer, ReadCompleteHandler handler) {

    socketEventData_.readQ.push(std::make_shared<ReadFullEvent>(reactor_, socketEventData_, buffer, handler));
    reactor_.registerRead(socketEventData_);
}


void StreamSocket::write(Buffer buffer, WriteCompleteHandler handler) {
    socketEventData_.writeQ.push(std::make_shared<WriteFullEvent>(reactor_, socketEventData_, buffer, handler));
    reactor_.registerWrite(socketEventData_);
}

SocketEventData& StreamSocket::socketEventData() {
    return socketEventData_;
}


