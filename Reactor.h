//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__REACTOR_H_
#define ASYNC_NET__REACTOR_H_
#include "detail/EpollWrapper.h"
#include "detail/NetEventData.h"


class Reactor {
public:

    void registerRead(NetEventData& socketEventData);
    void registerWrite(NetEventData& socketEventData);
    void add(NetEventData& socketEventData);

    void run();

    void stop();
private:
    bool isStop_{false};
    std::unique_ptr<EpollWrapper> wrapper_ = std::make_unique<EpollWrapper>();

};

#endif //ASYNC_NET__REACTOR_H_
