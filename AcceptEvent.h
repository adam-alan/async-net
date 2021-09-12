//
// Created by loadstar on 2021/9/12.
//

#ifndef ASYNC_NET__ACCEPTEVENT_H_
#define ASYNC_NET__ACCEPTEVENT_H_

#include <memory>
#include <functional>
#include "SocketEventHandler.h"
#include "StreamSocket.h"
#include "Reactor.h"

using AcceptHandler = std::function<void(std::error_code, StreamSocket)>;

class AcceptEvent: public SocketEventHandler, std::enable_shared_from_this<AcceptEvent>{
public:

    void handle() override;

private:
    Reactor& reactor_;
    SocketEventData& socketEventData_;
    AcceptHandler handler_;

};

#endif //ASYNC_NET__ACCEPTEVENT_H_
