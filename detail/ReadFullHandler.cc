//
// Created by loadstar on 2021/9/21.
//

#include "ReadFullHandler.h"
ReadFullHandler::ReadFullHandler(Reactor &reactor,
                                 int fd,
                                 const Buffer &buffer,
                                 const ReadWriteCompleteHandler &handler) : ReadWriteFullHandler(reactor,
                                                                                                 fd,
                                                                                                 buffer,
                                                                                                 handler) {}
ssize_t ReadFullHandler::io(int fd, void *buf, size_t n) {
    return ::read(fd, buf, n);
}

void ReadFullHandler::onComplete() {

}

void ReadFullHandler::onUnComplete() {
    reactor().registerRead(fd(), *this);
}
