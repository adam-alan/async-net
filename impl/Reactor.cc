//
// Created by loadstar on 2021/9/11.
//
#include <iostream>

#include "../Reactor.h"



void Reactor::run() {
    while (!isStop_) {
        epoll_event events[100];


        auto nfs = ::epoll_wait(wrapper_->epollFd(), events, 100, 100);
        for (int i = 0;i < nfs; ++i) {

            auto data = (NetEventData*)events[i].data.ptr;

            if (events[i].events == EPOLLOUT ) {
//                if (!data->connectQ.empty()) {
//                    auto front = data->connectQ.front();
//                    front->handle();
//                    data->connectQ.pop();
//                }

                if (!data->writeQ.empty()) {

                    data->writeQ.front()->handle();
                    data->writeQ.pop();
                }

            }

            if (events[i].events == EPOLLIN) {

                if (!data->readQ.empty()) {

                    data->readQ.front()->handle();
                    data->readQ.pop();
                }
            }
        }
    }
}


void Reactor::stop() {
    isStop_ = true;
}

void Reactor::registerRead(NetEventData& socketEventData) {
    ::epoll_event ev{};
    ev.events = EPOLLIN;
    ev.data.ptr = &socketEventData;

    if (wrapper_->modify(socketEventData.fd, ev)) {
        throw std::system_error{errno, std::system_category()};
    }
}

void Reactor::registerWrite(NetEventData& socketEventData) {
    ::epoll_event ev{};
    ev.events = EPOLLOUT;
    ev.data.ptr = &socketEventData;

    if (wrapper_->modify(socketEventData.fd, ev)) {
        throw std::system_error{errno, std::system_category()};
    }
}

void Reactor::add(NetEventData& socketEventData) {
    if (wrapper_->add(socketEventData.fd, {})) {
        throw std::system_error{errno, std::system_category()};
    }
}
