//
// Created by loadstar on 2021/9/12.
//

#include "../Acceptor.h"
Acceptor::Acceptor(Reactor& reactor, short port)
:reactor_(reactor)
, streamSocket_(reactor){
    streamSocket_.bind(port);
    streamSocket_.listen();
}


void Acceptor::accept(const AcceptCompleteHandler & handler) {
    reactor_.registerRead(std::make_shared<AcceptHandler>(streamSocket_.fd(), reactor_, handler));
}
