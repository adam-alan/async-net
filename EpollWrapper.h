//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__EPOLLWRAPPER_H_
#define ASYNC_NET__EPOLLWRAPPER_H_

#include <sys/epoll.h>
#include <system_error>

class EpollWrapper {
public:
    EpollWrapper();

    int epollFd() const noexcept;
    std::error_code add(int fd, epoll_event event);
    std::error_code del(int fd, epoll_event event);
    std::error_code modify(int fd, epoll_event event);
private:

    int epfd_;

};

#endif //ASYNC_NET__EPOLLWRAPPER_H_
