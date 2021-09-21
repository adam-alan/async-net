//
// Created by loadstar on 2021/9/13.
//

#include "../AcceptHandler.h"

#include <utility>


AcceptHandler::AcceptHandler(Reactor &reactor, int fd, AcceptCompleteHandler handler) : NetEventHandler(reactor,
                                                                                                        fd),
                                                                                        handler_(std::move(handler)) {}



void AcceptHandler::operator()() {

    int newSock = ::accept4(fd(), nullptr, nullptr, SOCK_CLOEXEC | SOCK_NONBLOCK);

    if (newSock < 0) {
        handler_(std::error_code{errno, std::system_category()}, std::make_shared<ReadWriteSocket>(reactor(), newSock));
        return;
    }

    handler_({}, std::make_shared<ReadWriteSocket>(reactor(), newSock));

}
