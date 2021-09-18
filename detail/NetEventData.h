//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__NETEVENTDATA_H_
#define ASYNC_NET__NETEVENTDATA_H_

#include <memory>
#include <queue>
#include <sys/epoll.h>
#include "NetEventHandler.h"



struct NetEventData {
    uint32_t events{};
    std::queue<std::shared_ptr<NetEventHandler>> readQ{};
    std::queue<std::shared_ptr<NetEventHandler>> writeQ{};
};

#endif //ASYNC_NET__NETEVENTDATA_H_
