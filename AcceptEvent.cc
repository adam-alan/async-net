//
// Created by loadstar on 2021/9/13.
//

#include "AcceptEvent.h"










void AcceptEvent::handle() {
    int newSock = ::accept4(socketEventData_.fd, nullptr, nullptr, SOCK_CLOEXEC | SOCK_NONBLOCK);
    if (newSock < 0) {
        StreamSocket streamSocket(reactor_, newSock);
        handler_(std::error_code{errno, std::system_category()}, streamSocket);
        return;
    }

    StreamSocket streamSocket(reactor_, newSock);
    handler_({}, streamSocket);


}
