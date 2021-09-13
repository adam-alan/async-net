//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__SOCKETEVENTDATA_H_
#define ASYNC_NET__SOCKETEVENTDATA_H_

#include <memory>
#include <queue>
#include <sys/epoll.h>
#include "SocketEventHandler.h"



struct SocketEventData {
    int fd{-1};
    std::queue<std::shared_ptr<SocketEventHandler>> readQ{};
    std::queue<std::shared_ptr<SocketEventHandler>> writeQ{};
};

#endif //ASYNC_NET__SOCKETEVENTDATA_H_
