//
// Created by loadstar on 2021/9/12.
//

#include "Acceptor.h"
Acceptor::Acceptor(Reactor& reactor, short port)
:reactor_(reactor)
, streamSocket_(reactor){
    streamSocket_.bind(port);
    streamSocket_.listen();
}


void Acceptor::accept(const AcceptHandler& handler) {

    auto acceptEvent = std::make_shared<AcceptEvent>(reactor_, streamSocket_.socketEventData(), handler);
    streamSocket_.socketEventData().readQ.push(acceptEvent);
    reactor_.registerRead(streamSocket_.socketEventData());

}
