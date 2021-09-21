//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__NETEVENTHANDLER_H_
#define ASYNC_NET__NETEVENTHANDLER_H_

#include "../Reactor.h"


class NetEventHandler {
public:

    NetEventHandler(Reactor &reactor, int fd) : reactor_(reactor), fd_(fd) {}

    [[nodiscard]] int fd() {
        return fd_;
    }

    [[nodiscard]] Reactor &reactor()  {
        return reactor_;
    }

private:
    Reactor& reactor_;
    int fd_{-1};
};

#endif //ASYNC_NET__NETEVENTHANDLER_H_
