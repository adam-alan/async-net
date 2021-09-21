//
// Created by loadstar on 2021/9/21.
//

#include "../ReadWriteFullHandler.h"

void ReadWriteFullHandler::operator()() {
    ssize_t bytes = io(fd(), buffer_.data(), buffer_.size());

    // 处理异常
    if (bytes <= 0) {
        handler_({errno, std::system_category()}, totalBytes_);
        return;
    }

    totalBytes_ += bytes;
    if (totalBytes_ == initSize_) {
        ioComplete();
        handler_({}, totalBytes_);
        return;
    }
    buffer_.moveStep(bytes);
    ioUnComplete();
}

