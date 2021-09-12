//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__REACTOR_H_
#define ASYNC_NET__REACTOR_H_

#include "EpollWrapper.h"
#include "SocketEventData.h"


class Reactor {
public:

    void registerEvent(SocketEventData socketEventData);

    void run();

    void stop();
private:
    bool stoped_{false};
    std::unique_ptr<EpollWrapper> wrapper_ = std::make_unique<EpollWrapper>();

};

#endif //ASYNC_NET__REACTOR_H_
