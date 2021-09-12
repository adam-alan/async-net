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
    auto readEvent = std::make_shared<ReadFullEvent>(reactor_, socketEventData_, buffer, handler);
    socketEventData_.event.events |= EPOLLIN;
    socketEventData_.event.data.ptr = &socketEventData_;
    socketEventData_.readQ.push(readEvent);
    reactor_.registerEvent(socketEventData_);
}


void StreamSocket::write(Buffer buffer, WriteCompleteHandler handler) {
    auto writeEvent = std::make_shared<WriteFullEvent>(reactor_, socketEventData_, buffer, handler);
    epoll_event event{0};
    event.events |= EPOLLOUT;

    if(socketEventData_.writeQ.empty()) {
        if ((socketEventData_.event.events & EPOLLOUT) == 0) {
            event.events |= socketEventData_.event.events | EPOLLOUT;
        }
    } else {
        event.events |= socketEventData_.event.events | EPOLLOUT;
    }
    socketEventData_.event.events |= event.events;
    socketEventData_.event.data.ptr = &socketEventData_;
    socketEventData_.writeQ.push(writeEvent);
    reactor_.registerEvent(socketEventData_);
}


