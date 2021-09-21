//
// Created by loadstar on 2021/9/21.
//

#ifndef ASYNC_NET_DETAIL_READWRITEFULLHANDLER_H_
#define ASYNC_NET_DETAIL_READWRITEFULLHANDLER_H_
#include <system_error>
#include <utility>
#include "NetEventHandler.h"
#include "../Buffer.h"

using ReadWriteCompleteHandler = std::function<void(std::error_code, size_t)>;


class ReadWriteFullHandler: public NetEventHandler{
public:
    ReadWriteFullHandler(Reactor &reactor,
                         int fd,
                         const Buffer &buffer,
                         ReadWriteCompleteHandler handler) : NetEventHandler(reactor, fd),
                                                                buffer_(buffer),
                                                                handler_(std::move(handler)) {}
protected:
    virtual ssize_t io(int fd, void* buf, size_t n) = 0;
    virtual void onComplete() = 0;
    virtual void onUnComplete() = 0;
public:
    void operator()();
private:

    Buffer buffer_;
    size_t totalBytes_{0};
    size_t initSize_{buffer_.size()};
    ReadWriteCompleteHandler handler_;

};

#endif //ASYNC_NET_DETAIL_READWRITEFULLHANDLER_H_
