//
// Created by loadstar on 2021/9/12.
//

#include "../Acceptor.h"
Acceptor::Acceptor(Reactor& reactor, short port)
:reactor_(reactor)
, listenSocket_(reactor){
    listenSocket_.bind(port);
    listenSocket_.listen();
}


void Acceptor::accept(const AcceptCompleteHandler & handler) {
    listenSocket_.accept(handler);
}
