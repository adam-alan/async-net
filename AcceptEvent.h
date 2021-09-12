//
// Created by loadstar on 2021/9/12.
//

#ifndef ASYNC_NET__ACCEPTEVENT_H_
#define ASYNC_NET__ACCEPTEVENT_H_

#include <memory>
#include "SocketEventHandler.h"


class AcceptEvent: public SocketEventHandler, std::enable_shared_from_this<AcceptEvent>{
public:

    void handle() override {

    }


};

#endif //ASYNC_NET__ACCEPTEVENT_H_
