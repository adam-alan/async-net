//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__WRITEFULL_H_
#define ASYNC_NET__WRITEFULL_H_

#include <iostream>
#include <memory>
#include <functional>
#include <sys/epoll.h>

#include "../Buffer.h"
#include "../Reactor.h"

using WriteCompleteHandler = std::function<void(std::error_code, size_t)>;

class WriteFullHandler: public NetEventHandler, public std::enable_shared_from_this<WriteFullHandler>{
public:
    WriteFullHandler(Reactor &reactor,
                     NetEventData& socketEventData,
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
        ssize_t bytes = ::write(socketEventData_.fd, buffer_.data(), buffer_.size());
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
        socketEventData_.writeQ.push(shared_from_this());
        reactor_.registerWrite(socketEventData_);
    }

private:


    Reactor& reactor_;
    NetEventData& socketEventData_;
    Buffer buffer_;
    WriteCompleteHandler handler_;
    size_t totalBytes_{0};
    size_t initSize_{buffer_.size()};
};

#endif //ASYNC_NET__WRITEFULL_H_
