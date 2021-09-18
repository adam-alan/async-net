//
// Created by loadstar on 2021/9/11.
//
#include <iostream>

#include "../Reactor.h"


void Reactor::add(int fd) {
    fdToEventData.insert({fd, std::make_shared<NetEventData>()});
    if (wrapper_->add(fd, {})) {
        throw std::system_error{errno, std::system_category()};
    }
}
void Reactor::registerRead(std::shared_ptr<NetEventHandler> handler) {
    fdToEventData[handler->fd()]->readQ.push(handler);
    fdToEventData[handler->fd()]->events |= EPOLLIN;
    std::cout << fdToEventData[handler->fd()]->events << std::endl;

    ::epoll_event ev{};
    ev.events = fdToEventData[handler->fd()]->events;
    ev.data.fd = handler->fd();
    if (wrapper_->modify(handler->fd(), ev)) {
        throw std::system_error{errno, std::system_category()};
    }
}
void Reactor::registerWrite(std::shared_ptr<NetEventHandler> handler) {
    fdToEventData[handler->fd()]->writeQ.push(handler);

    fdToEventData[handler->fd()]->events |= EPOLLOUT;
    std::cout << fdToEventData[handler->fd()]->events << std::endl;
    ::epoll_event ev{};
    ev.events = fdToEventData[handler->fd()]->events;
    ev.data.fd = handler->fd();
    if (wrapper_->modify(handler->fd(), ev)) {
        throw std::system_error{errno, std::system_category()};
    }
}


void Reactor::run() {
    while (!isStop_) {
        epoll_event events[100];

        auto nfs = ::epoll_wait(wrapper_->epollFd(), events, 100, 100);
        for (int i = 0;i < nfs; ++i) {

            auto data = fdToEventData[events[i].data.fd];

            if (events[i].events & EPOLLOUT ) {
                if (!data->writeQ.empty()) {
                    data->writeQ.front()->handle();
                    data->writeQ.pop();
                }
            }

            if (events[i].events & EPOLLIN) {
                if (!data->readQ.empty()) {
                    std::cout << "READ" << std::endl;
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


