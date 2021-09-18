//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__WRITEFULL_H_
#define ASYNC_NET__WRITEFULL_H_

#include <iostream>
#include <memory>
#include <functional>
#include <utility>
#include <sys/epoll.h>

#include "../Buffer.h"
#include "../Reactor.h"

using WriteCompleteHandler = std::function<void(std::error_code, size_t)>;

class WriteFullHandler: public NetEventHandler, public std::enable_shared_from_this<WriteFullHandler>{
public:
    WriteFullHandler(
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
        ssize_t bytes = ::write(fd(), buffer_.data(), buffer_.size());
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
        buffer_.moveStep(bytes);
//        netEventData_->writeQ.push(shared_from_this());
//        reactor_.registerWrite(netEventData_);
        reactor_.registerRead(shared_from_this());
    }

private:

    Reactor& reactor_;
    Buffer buffer_;
    WriteCompleteHandler handler_;
    size_t totalBytes_{0};
    size_t initSize_{buffer_.size()};
};

#endif //ASYNC_NET__WRITEFULL_H_
