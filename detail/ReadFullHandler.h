//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__READFULL_H_
#define ASYNC_NET__READFULL_H_

#include "ReadWriteFullHandler.h"

class ReadFullHandler: public ReadWriteFullHandler{
public:
    ReadFullHandler(Reactor &reactor, int fd, const Buffer &buffer, const ReadWriteCompleteHandler &handler);
protected:
    ssize_t io(int fd, void *buf, size_t n) override;
    void onComplete() override;
    void onUnComplete() override;
};
#endif //ASYNC_NET__READFULL_H_
