//
// Created by loadstar on 2021/9/12.
//

#ifndef ASYNC_NET__ACCEPTOR_H_
#define ASYNC_NET__ACCEPTOR_H_

#include "StreamSocket.h"

using AcceptHandler = std::function<void(std::error_code, StreamSocket)>;


class Acceptor {

public:
    Acceptor(Reactor reactor, short port);


    void accept(AcceptHandler handler);

private:

    Reactor& reactor_;
    StreamSocket streamSocket_;

};

#endif //ASYNC_NET__ACCEPTOR_H_
