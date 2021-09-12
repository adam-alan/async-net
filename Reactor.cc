//
// Created by loadstar on 2021/9/11.
//

#include "Reactor.h"

void Reactor::registerEvent(SocketEventData socketEventData) {
    auto ec = wrapper_->modify(socketEventData.fd, socketEventData.event);

    if (ec) {
        throw std::system_error(ec);
    }

}

void Reactor::run() {
    while (!stoped_) {
        epoll_event events[100];


        auto nfs = ::epoll_wait(wrapper_->epollFd(), events, 100, 100);
        for (int i = 0;i < nfs; ++i) {
            SocketEventData* data = (SocketEventData*)events[i].data.ptr;
//
//            if (events[i].events == EPOLLOUT ) {
//                if (data->connectQ.size()) {
//                    auto front = data->connectQ.front();
//                    front->handle();
//                    data->connectQ.pop();
//                }
//
//                if (data->writeQ.size()) {
//                    auto front = data->writeQ.front();
//                    front->handle();
//                    data->writeQ.pop();
//                }
//
//            }
//
//            if (events[i].events == EPOLLIN) {
//                if (data->readQ.size()) {
//                    auto front = data->readQ.front();
//                    front->handle();
//                    data->readQ.pop();
//                }
//            }
        }
    }
}

void Reactor::stop() {
    stoped_ = true;
}
