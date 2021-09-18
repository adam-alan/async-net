//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__READFULL_H_
#define ASYNC_NET__READFULL_H_
#include <iostream>
#include <memory>
#include <sys/epoll.h>
#include <functional>
#include <utility>

#include "../Buffer.h"
#include "../Reactor.h"

using ReadCompleteHandler = std::function<void(std::error_code, size_t)>;

class ReadFullHandler: public NetEventHandler, public std::enable_shared_from_this<ReadFullHandler> {
public:

    ReadFullHandler(
        int fd
        , Reactor &reactor
        , const Buffer &buffer
        , ReadCompleteHandler handler

    ): NetEventHandler(fd)
    , reactor_(reactor)
    , buffer_(buffer)
    , handler_(std::move(handler))
    , totalBytes_(0)
    , initSize_(buffer_.size()) {

    }

    void handle() override {
        ssize_t bytes = ::read(fd(), buffer_.data(), buffer_.size());
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

        reactor_.registerRead(shared_from_this());


    }

private:

    Reactor& reactor_;
    Buffer buffer_;
    ReadCompleteHandler handler_;
    size_t totalBytes_{0};
    size_t initSize_{buffer_.size()};
};
#endif //ASYNC_NET__READFULL_H_
