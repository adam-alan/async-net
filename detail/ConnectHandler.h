//
// Created by loadstar on 2021/9/12.
//

#ifndef ASYNC_NET__CONNECTEVENT_H_
#define ASYNC_NET__CONNECTEVENT_H_

#include "NetEventHandler.h"
#include <memory>
#include <functional>

using ConnectCompleteHandler = std::function<void(std::error_code)>;

class ConnectHandler: public NetEventHandler, std::enable_shared_from_this<ConnectHandler>{

};

#endif //ASYNC_NET__CONNECTEVENT_H_
