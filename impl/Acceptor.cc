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


void Acceptor::accept(const AcceptHandler& handler) {

    streamSocket_.socketEventData().readQ.push(std::make_shared<AcceptHandler>(reactor_, streamSocket_.socketEventData(), handler));
    reactor_.registerRead(streamSocket_.socketEventData());

}
