//
// Created by loadstar on 2021/9/13.
//
#include <fcntl.h>

auto makeNoBlock(int fd) {
    auto status = ::fcntl(fd, F_GETFL);
    status |= O_NONBLOCK;
    ::fcntl(fd, F_SETFL, status);
}
