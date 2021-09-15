//
// Created by loadstar on 2021/9/13.
//

#include "../AcceptEvent.h"




AcceptEvent::AcceptEvent(Reactor &reactor, NetEventData socketEventData, AcceptHandler acceptHandler)
:reactor_(reactor)
, socketEventData_(socketEventData)
, handler_(acceptHandler){

}






void AcceptEvent::handle() {

    int newSock = ::accept4(socketEventData_.fd, nullptr, nullptr, SOCK_CLOEXEC | SOCK_NONBLOCK);

    if (newSock < 0) {
        handler_(std::error_code{errno, std::system_category()}, std::make_shared<StreamSocket>(reactor_, newSock));
        return;
    }

    handler_({}, std::make_shared<StreamSocket>(reactor_, newSock));

}
