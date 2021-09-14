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

    explicit StreamSocket(Reactor& reactor);

    StreamSocket(Reactor& reactor, int fd);

    StreamSocket(StreamSocket&& streamSocket) noexcept ;

    StreamSocket& operator=(StreamSocket&& streamSocket) noexcept;

    void bind(short port) const;

    void listen();

    void read(Buffer buffer, ReadCompleteHandler handler);

    void write(Buffer buffer, WriteCompleteHandler handler);

    SocketEventData& socketEventData();

    ~StreamSocket() {
        std::cout << "destroyed" << std::endl;
    }
private:

    Reactor& reactor_;
    SocketEventData socketEventData_;

};







#endif //ASYNC_NET__STREAMSOCKET_H_
