//
// Created by loadstar on 2021/9/20.
//

#ifndef ASYNC_NET_DETAIL_READUNTILHANDLER_H_
#define ASYNC_NET_DETAIL_READUNTILHANDLER_H_

#include "NetEventHandler.h"
#include <memory>

class ReadUntilHandler: public NetEventHandler, public std::enable_shared_from_this<ReadUntilHandler>{

public:
    void handle() override {

    }
};

#endif //ASYNC_NET_DETAIL_READUNTILHANDLER_H_
