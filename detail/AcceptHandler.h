//
// Created by loadstar on 2021/9/12.
//

#ifndef ASYNC_NET__ACCEPTEVENT_H_
#define ASYNC_NET__ACCEPTEVENT_H_

#include <memory>
#include <functional>
#include "NetEventHandler.h"
#include "../ReadWriteSocket.h"
#include "../Reactor.h"

using AcceptCompleteHandler = std::function<void(std::error_code, std::shared_ptr<ReadWriteSocket>)>;

class AcceptHandler: public NetEventHandler{
public:
    AcceptHandler(Reactor &reactor, int fd, AcceptCompleteHandler handler);

    void operator()();

private:
    AcceptCompleteHandler handler_;
};

#endif //ASYNC_NET__ACCEPTEVENT_H_
