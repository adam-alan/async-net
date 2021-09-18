//
// Created by loadstar on 2021/9/13.
//

#include "../AcceptHandler.h"

#include <utility>






AcceptHandler::AcceptHandler(int fd, Reactor &reactor, AcceptCompleteHandler handler)
: NetEventHandler(fd), reactor_(reactor), handler_(std::move(handler)) {

}



void AcceptHandler::handle() {

    int newSock = ::accept4(fd(), nullptr, nullptr, SOCK_CLOEXEC | SOCK_NONBLOCK);

    if (newSock < 0) {
        handler_(std::error_code{errno, std::system_category()}, {reactor_, newSock});
        return;
    }

    handler_({}, {reactor_, newSock});

}
