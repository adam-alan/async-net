//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__NETEVENTHANDLER_H_
#define ASYNC_NET__NETEVENTHANDLER_H_




class NetEventHandler {
public:
    explicit NetEventHandler(int fd) {
        this->fd_ = fd;
    }

    int fd() const {
        return fd_;
    }
    virtual void handle() = 0;

private:
    int fd_{-1};
};

#endif //ASYNC_NET__NETEVENTHANDLER_H_
