//
// Created by loadstar on 2021/9/12.
//

#ifndef ASYNC_NET__ACCEPTOR_H_
#define ASYNC_NET__ACCEPTOR_H_

#include "ReadWriteSocket.h"
#include "detail/AcceptHandler.h"
#include "ListenSocket.h"



class Acceptor {

public:
    Acceptor(Reactor& reactor, short port);
    void accept(const AcceptCompleteHandler & handler);

private:

    Reactor& reactor_;
    ListenSocket listenSocket_;


};

#endif //ASYNC_NET__ACCEPTOR_H_
