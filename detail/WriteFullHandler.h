//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__WRITEFULL_H_
#define ASYNC_NET__WRITEFULL_H_



#include "ReadWriteFullHandler.h"

class WriteFullHandler: public ReadWriteFullHandler {
public:

    WriteFullHandler(Reactor &reactor,
                     int fd,
                     const Buffer &buffer,
                     const ReadWriteCompleteHandler &handler);

protected:
    ssize_t io(int fd, void *buf, size_t n) override;
    void ioComplete() override;
    void ioUnComplete() override;

};

#endif //ASYNC_NET__WRITEFULL_H_
