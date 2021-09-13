//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__READFULL_H_
#define ASYNC_NET__READFULL_H_
#include <iostream>
#include <memory>
#include <sys/epoll.h>
#include <functional>

#include "Buffer.h"
#include "Reactor.h"

using ReadCompleteHandler = std::function<void(std::error_code, size_t)>;

class ReadFullEvent: public SocketEventHandler, public std::enable_shared_from_this<ReadFullEvent> {
public:


    ReadFullEvent(Reactor &reactor,
                  SocketEventData& socketEventData,
                  const Buffer &buffer,
                  ReadCompleteHandler handler)
    : reactor_(reactor)
    , socketEventData_(socketEventData)
    , buffer_(buffer)
    , handler_(std::move(handler))
    , totalBytes_{0}
    , initSize_{buffer_.size()} {

    }

    void handle() override {
        std::cout << "ReadFullEvent" << std::endl;
        ssize_t bytes = ::read(socketEventData_.fd, buffer_.data(), buffer_.size());
        // 处理异常
        if (bytes <= 0) {
            handler_({errno, std::system_category()}, totalBytes_);
            return;
        }

        totalBytes_ += bytes;
        if (totalBytes_ == initSize_) {
            handler_({}, totalBytes_);
            return;
        }

        registerEvent();
    }

private:
    void registerEvent() {

        socketEventData_.readQ.push(shared_from_this());
        reactor_.registerWrite(socketEventData_);
    }

    Reactor& reactor_;
    SocketEventData& socketEventData_;
    Buffer buffer_;
    ReadCompleteHandler handler_;
    size_t totalBytes_{0};
    size_t initSize_{buffer_.size()};
};
#endif //ASYNC_NET__READFULL_H_
