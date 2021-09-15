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

using AcceptHandler = std::function<void(std::error_code, std::shared_ptr<StreamSocket>)>;

class AcceptEvent: public NetEventHandler, std::enable_shared_from_this<AcceptEvent>{
public:
    AcceptEvent(Reactor& reactor, NetEventData socketEventData, AcceptHandler acceptHandler);
    void handle() override;
private:
    Reactor& reactor_;
    NetEventData socketEventData_;
    AcceptHandler handler_;

};

#endif //ASYNC_NET__ACCEPTEVENT_H_
