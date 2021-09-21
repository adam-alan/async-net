//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__REACTOR_H_
#define ASYNC_NET__REACTOR_H_
#include "detail/EpollWrapper.h"
#include "detail/NetEventData.h"
#include <unordered_map>
#include <functional>

class Reactor {
public:

    void add(int fd);
//    void registerRead(std::shared_ptr<NetEventHandler> handler);
//
//    void registerWrite(std::shared_ptr<NetEventHandler> handler);
//    void registerUnWrite(std::shared_ptr<NetEventHandler> handler);

    void registerRead(int fd, std::function<void()> handler);
    void registerWrite(int fd, std::function<void()> handler);
    void registerUnWrite(int fd, std::function<void()> handler);


    void run();
    void stop();
private:
    bool isStop_{false};
    std::unique_ptr<EpollWrapper> wrapper_ = std::make_unique<EpollWrapper>();
    std::unordered_map<int, std::shared_ptr<NetEventData>> fdToEventData{};


};

#endif //ASYNC_NET__REACTOR_H_
