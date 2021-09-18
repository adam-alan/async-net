//
// Created by loadstar on 2021/9/12.
//

#ifndef ASYNC_NET__ACCEPTEVENT_H_
#define ASYNC_NET__ACCEPTEVENT_H_

#include <memory>
#include <functional>
#include "NetEventHandler.h"
#include "../StreamSocket.h"
#include "../Reactor.h"

using AcceptCompleteHandler = std::function<void(std::error_code, StreamSocket)>;

class AcceptHandler: public NetEventHandler, std::enable_shared_from_this<AcceptHandler>{
public:
    AcceptHandler(int fd, Reactor &reactor, AcceptCompleteHandler handler);
    void handle() override;
private:
    Reactor& reactor_;
    AcceptCompleteHandler handler_;
};

#endif //ASYNC_NET__ACCEPTEVENT_H_
