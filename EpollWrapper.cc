//
// Created by loadstar on 2021/9/11.
//

#include "EpollWrapper.h"


EpollWrapper::EpollWrapper() {
    epfd_ = ::epoll_create1(EPOLL_CLOEXEC);

    if(epfd_ < 0) {
        throw std::system_error(errno, std::system_category());
    }
}
int EpollWrapper::epollFd() const noexcept {
    return epfd_;
}

std::error_code EpollWrapper::add(int fd, epoll_event event) {
    return ::epoll_ctl(epfd_, EPOLL_CTL_ADD, fd, &event)
            ? std::error_code(errno, std::system_category())
            : std::error_code();
}

std::error_code EpollWrapper::del(int fd, epoll_event event) {
    return ::epoll_ctl(epfd_, EPOLL_CTL_DEL, fd, &event)
           ? std::error_code(errno, std::system_category())
           : std::error_code();
}

std::error_code EpollWrapper::modify(int fd, epoll_event event) {
    return ::epoll_ctl(epfd_, EPOLL_CTL_MOD, fd, &event)
           ? std::error_code(errno, std::system_category())
           : std::error_code();
}


