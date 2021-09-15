#include <iostream>
#include <thread>
#include "StreamSocket.h"
#include "Acceptor.h"

void doAccept(Acceptor& acceptor, std::vector<std::shared_ptr<StreamSocket>>& sockets) {
    acceptor.accept([&](std::error_code ec, std::shared_ptr<StreamSocket> streamSocket){
        sockets.push_back(streamSocket);
        char buf[] = "hello";
        streamSocket->write(buffer(buf), [](std::error_code ec, size_t bytes){
            if(!ec) {
                std::cout << "write success with bytes of " << bytes << std::endl;
            }
        });
        doAccept(acceptor, sockets);
    });
}




int main() {

//    Reactor reactor;
//    Acceptor acceptor(reactor, 12345);
//    std::vector<std::shared_ptr<StreamSocket>> sockets;
//    doAccept(acceptor, sockets);
//
//    reactor.run();
    char str[] = "hello";
    std::cout << buffer(str).data() << std::endl;
    return 0;
}
