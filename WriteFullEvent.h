//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__WRITEFULL_H_
#define ASYNC_NET__WRITEFULL_H_

#include <iostream>
#include <memory>
#include <functional>
#include <sys/epoll.h>

#include "Buffer.h"
#include "Reactor.h"

using WriteCompleteHandler = std::function<void(std::error_code, size_t)>;

class WriteFullEvent: public SocketEventHandler, public std::enable_shared_from_this<WriteFullEvent>{
public:
    WriteFullEvent(Reactor &reactor,
                   SocketEventData &socketEventData,
                   const Buffer &buffer,
                   WriteCompleteHandler handler)
    : reactor_(reactor)
    , socketEventData_(socketEventData)
    , buffer_(buffer)
    , handler_(std::move(handler))
    , totalBytes_{0}
    , initSize_{buffer_.size()}{

    }

    void handle() override {
        std::cout << "WriteFullEvent" << std::endl;
        ssize_t bytes = ::write(socketEventData_.fd, buffer_.data(), buffer_.size());
        // 处理异常
        if (bytes <= 0) {
            handler_(std::error_code(errno, std::system_category()), totalBytes_);
            return;
        }

        totalBytes_ += bytes;
        if (totalBytes_ == initSize_) {
            handler_(std::error_code(), totalBytes_);
            return;
        }
        registerEvent();
    }

private:
    void registerEvent() {
        epoll_event event{0};
        event.events |= EPOLLOUT;

        if(socketEventData_.writeQ.empty()) {
            if ((socketEventData_.event.events & EPOLLOUT) == 0) {
                event.events |= socketEventData_.event.events | EPOLLOUT;
            }
        } else {
            event.events |= socketEventData_.event.events | EPOLLOUT;
        }
        socketEventData_.event.events |= event.events;
        socketEventData_.event.data.ptr = &socketEventData_;
        socketEventData_.writeQ.push(shared_from_this());
        reactor_.registerEvent(socketEventData_);

    }

    Reactor& reactor_;
    SocketEventData& socketEventData_;
    Buffer buffer_;
    WriteCompleteHandler handler_;
    size_t totalBytes_{};
    size_t initSize_{buffer_.size()};
};

#endif //ASYNC_NET__WRITEFULL_H_
