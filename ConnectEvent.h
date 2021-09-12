//
// Created by loadstar on 2021/9/12.
//

#ifndef ASYNC_NET__CONNECTEVENT_H_
#define ASYNC_NET__CONNECTEVENT_H_

#include "SocketEventHandler.h"
#include <memory>

class ConnectEvent: public SocketEventHandler, std::enable_shared_from_this<ConnectEvent>{

};

#endif //ASYNC_NET__CONNECTEVENT_H_
