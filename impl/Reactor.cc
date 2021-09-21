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

void Reactor::run() {
    while (!isStop_) {
        epoll_event events[100];

        auto nfs = ::epoll_wait(wrapper_->epollFd(), events, 100, 100);
        for (int i = 0;i < nfs; ++i) {

            auto data = fdToEventData[events[i].data.fd];
            std::cout << events[i].events << std::endl;
            if (events[i].events & EPOLLOUT ) {
                if (!data->writeQueue.empty()) {
                    data->writeQueue.front()();
                    data->writeQueue.pop();
                }
            }

            if (events[i].events & EPOLLIN) {
                if (!data->readQueue.empty()) {
                    std::cout << "READ" << std::endl;
                    data->readQueue.front()();
                    data->readQueue.pop();
                }
            }
        }
    }
}


void Reactor::stop() {
    isStop_ = true;
}
void Reactor::registerRead(int fd, std::function<void()> handler) {
    fdToEventData[fd]->readQueue.push(handler);
    fdToEventData[fd]->events |= EPOLLIN | EPOLLET;
    ::epoll_event ev{};
    ev.events = fdToEventData[fd]->events;
    ev.data.fd = fd;
    if (wrapper_->modify(fd, ev)) {
        throw std::system_error{errno, std::system_category()};
    }
}
void Reactor::registerWrite(int fd, std::function<void()> handler) {
    fdToEventData[fd]->readQueue.push(handler);
    fdToEventData[fd]->events |= EPOLLOUT | EPOLLET;
    ::epoll_event ev{};
    ev.events = fdToEventData[fd]->events;
    ev.data.fd = fd;
    if (wrapper_->modify(fd, ev)) {
        throw std::system_error{errno, std::system_category()};
    }
}
void Reactor::registerUnWrite(int fd, std::function<void()> handler) {
    fdToEventData[fd]->readQueue.push(handler);
    fdToEventData[fd]->events &= ~EPOLLOUT;
    ::epoll_event ev{};
    ev.events = fdToEventData[fd]->events;
    ev.data.fd = fd;
    if (wrapper_->modify(fd, ev)) {
        throw std::system_error{errno, std::system_category()};
    }
}


