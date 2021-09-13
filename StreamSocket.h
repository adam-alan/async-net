//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__STREAMSOCKET_H_
#define ASYNC_NET__STREAMSOCKET_H_

#include <memory>
#include <functional>
#include "Buffer.h"
#include "SocketEventData.h"
#include "Reactor.h"
#include "ReadFullEvent.h"
#include "WriteFullEvent.h"
#include "SocketUtils.h"
#include <sys/socket.h>
#include <netinet/in.h>
using ConnectHandler = std::function<void(std::error_code)>;



class StreamSocket {
public:

    explicit StreamSocket(Reactor& reactor)
    : reactor_(reactor)
    , socketEventData_{}{
        socketEventData_.fd = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (socketEventData_.fd < 0) {
            throw std::system_error(errno, std::system_category());
        }
        makeNoBlock(socketEventData_.fd);
        reactor_.add(socketEventData_);

    }


    StreamSocket(Reactor& reactor, int fd)
        : reactor_(reactor){
        socketEventData_.fd = fd;
        reactor_.add(socketEventData_);

    }
    void bind(short port) const;

    void listen();

    void read(Buffer buffer, ReadCompleteHandler handler);

    void write(Buffer buffer, WriteCompleteHandler handler);
    SocketEventData& socketEventData();
//    void accept()

private:

    Reactor& reactor_;


    SocketEventData socketEventData_;

};







#endif //ASYNC_NET__STREAMSOCKET_H_
