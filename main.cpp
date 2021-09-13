#include <iostream>
#include <thread>
#include "StreamSocket.h"
#include "Acceptor.h"






int main() {

    Reactor reactor;
    Acceptor acceptor(reactor, 12345);
    acceptor.accept([](std::error_code ec, std::shared_ptr<StreamSocket> streamSocket){
        char str[] = "hello";

        std::cout << "accept" << std::endl;
        std::cout << &streamSocket->socketEventData().writeQ << std::endl;
        streamSocket->write(buffer(str), [](std::error_code ec, size_t bytes){
            if(!ec) {
                std::cout << "write success" << std::endl;
            }
        });
    });
    reactor.run();
    return 0;
}
