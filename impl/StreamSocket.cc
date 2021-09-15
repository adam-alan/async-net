//
// Created by loadstar on 2021/9/11.
//

#include <netinet/in.h>

#include "../StreamSocket.h"

StreamSocket::StreamSocket(Reactor& reactor)
: reactor_(reactor)
, socketEventData_{}{
    socketEventData_.fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socketEventData_.fd < 0) {
        throw std::system_error(errno, std::system_category());
    }
    makeNoBlock(socketEventData_.fd);
    reactor_.add(socketEventData_);

}

StreamSocket::StreamSocket(Reactor& reactor, int fd)
: reactor_(reactor){
    socketEventData_.fd = fd;
    reactor_.add(socketEventData_);
}
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

    socketEventData_.readQ.push(std::make_shared<ReadFull>(reactor_, socketEventData_, buffer, handler));
    reactor_.registerRead(socketEventData_);
}


void StreamSocket::write(Buffer buffer, WriteCompleteHandler handler) {
    socketEventData_.writeQ.push(std::make_shared<WriteFull>(reactor_, socketEventData_, buffer, handler));
    reactor_.registerWrite(socketEventData_);
}

NetEventData& StreamSocket::socketEventData() {
    return socketEventData_;
}

StreamSocket::StreamSocket(StreamSocket &&streamSocket) noexcept
:reactor_(streamSocket.reactor_)
, socketEventData_(std::move(streamSocket.socketEventData_))
{

}
StreamSocket &StreamSocket::operator=(StreamSocket &&streamSocket)  noexcept {
//    return <#initializer#>;
    return *this;
}


