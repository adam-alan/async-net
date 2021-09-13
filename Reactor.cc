//
// Created by loadstar on 2021/9/11.
//
#include <iostream>

#include "Reactor.h"



void Reactor::run() {
    while (!stoped_) {
        epoll_event events[100];


        auto nfs = ::epoll_wait(wrapper_->epollFd(), events, 100, 100);
        for (int i = 0;i < nfs; ++i) {

            auto data = (SocketEventData*)events[i].data.ptr;
//            std::cout << data->writeQ.size() << std::endl;
//            std::cout << data->connectQ.size() << std::endl;
//            std::cout << data->readQ.size() << std::endl;
            if (events[i].events == EPOLLOUT ) {
//                if (!data->connectQ.empty()) {
//                    auto front = data->connectQ.front();
//                    front->handle();
//                    data->connectQ.pop();
//                }

                if (!data->writeQ.empty()) {
                    std::cout << data << std::endl;

                    std::cout << "write register" << std::endl;
                    std::cout << data->writeQ.size() << std::endl;
                    std::cout << data->readQ.size() << std::endl;
                    if (data->writeQ.front() == nullptr) {
                        std::cout << "null" << std::endl;
                    }

                    data->writeQ.pop();
                }

            }

            if (events[i].events == EPOLLIN) {

                if (!data->readQ.empty()) {

                    data->readQ.front()->handle();
//
                    data->readQ.pop();
                }
            }
        }
    }
}


void Reactor::stop() {
    stoped_ = true;
}

void Reactor::registerRead(SocketEventData& socketEventData) {
    ::epoll_event ev{};
    ev.events = EPOLLIN;
    ev.data.ptr = &socketEventData;

    if (wrapper_->modify(socketEventData.fd, ev)) {
        throw std::system_error{errno, std::system_category()};
    }
}

void Reactor::registerWrite(SocketEventData& socketEventData) {
    ::epoll_event ev{};
    ev.events = EPOLLOUT;
    ev.data.ptr = &socketEventData;
    std::cout << &socketEventData << std::endl;

    if (wrapper_->modify(socketEventData.fd, ev)) {
        throw std::system_error{errno, std::system_category()};
    }
}

void Reactor::add(SocketEventData& socketEventData) {
    if (wrapper_->add(socketEventData.fd, {})) {
        throw std::system_error{errno, std::system_category()};
    }
}
