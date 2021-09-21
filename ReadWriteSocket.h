//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__READWRITESOCKET_H_
#define ASYNC_NET__READWRITESOCKET_H_

#include <memory>
#include <functional>
#include "Buffer.h"
#include "detail/NetEventData.h"
#include "Reactor.h"
#include "detail/ReadFullHandler.h"
#include "detail/WriteFullHandler.h"
#include "detail/FdUtils.h"
#include <sys/socket.h>
#include <netinet/in.h>


class ReadWriteSocket: public std::enable_shared_from_this<ReadWriteSocket>{
public:

    explicit ReadWriteSocket(Reactor& reactor);

    ReadWriteSocket(Reactor& reactor, int fd);


    void bind(short port) const;

    void listen();

    void read(Buffer buffer, const ReadWriteCompleteHandler& handler);

    void write(Buffer buffer, const ReadWriteCompleteHandler& handler);

private:

    Reactor& reactor_;
    int fd_;
};







#endif //ASYNC_NET__READWRITESOCKET_H_
