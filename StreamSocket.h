//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__STREAMSOCKET_H_
#define ASYNC_NET__STREAMSOCKET_H_

#include <memory>
#include <functional>
#include "Buffer.h"
#include "detail/NetEventData.h"
#include "Reactor.h"
#include "detail/ReadFullHandler.h"
#include "detail/WriteFullHandler.h"
#include "FdUtils.h"
#include <sys/socket.h>
#include <netinet/in.h>
using ConnectHandler = std::function<void(std::error_code)>;



class StreamSocket {
public:

    explicit StreamSocket(Reactor& reactor);

    StreamSocket(Reactor& reactor, int fd);

    int fd() const;
    void bind(short port) const;

    void listen();

    void read(Buffer buffer, ReadCompleteHandler handler);

    void write(Buffer buffer, WriteCompleteHandler handler);

private:

    Reactor& reactor_;
    int fd_;
};







#endif //ASYNC_NET__STREAMSOCKET_H_
