//
// Created by loadstar on 2021/9/20.
//

#ifndef ASYNC_NET__LISTENSOCKET_H_
#define ASYNC_NET__LISTENSOCKET_H_

#include "Reactor.h"
#include "detail/AcceptHandler.h"

class ListenSocket {
public:

    explicit ListenSocket(Reactor& reactor);

    void bind(short port) const;

    void listen() const;

    void accept(AcceptCompleteHandler handler);
private:

    Reactor& reactor_;
    int fd_;
};

#endif //ASYNC_NET__LISTENSOCKET_H_
