//
// Created by loadstar on 2021/9/21.
//

#include <unistd.h>

#include "../WriteFullHandler.h"

WriteFullHandler::WriteFullHandler(Reactor &reactor,
                                   int fd,
                                   const Buffer &buffer,
                                   const ReadWriteCompleteHandler &handler) : ReadWriteFullHandler(reactor,
                                                                                               fd,
                                                                                               buffer,
                                                                                               handler) {}

ssize_t WriteFullHandler::io(int fd, void *buf, size_t n) {
    return ::write(fd, buf, n);
}

void WriteFullHandler::onComplete() {
    reactor().registerUnWrite(fd(), *this);
}

void WriteFullHandler::onUnComplete() {
    reactor().registerWrite(fd(), *this);
}