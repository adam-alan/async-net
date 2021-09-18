#include <iostream>
#include <thread>
#include "StreamSocket.h"
#include "Acceptor.h"

char writeBuf[] = "hello";

char readBuf[6];

void doAccept(Acceptor& acceptor) {
    acceptor.accept([&](std::error_code ec, StreamSocket streamSocket){
        streamSocket.write(buffer(writeBuf), [](std::error_code ec, size_t bytes){
            if(!ec) {
                std::cout << "write success with bytes of " << bytes << std::endl;
            }
        });
        streamSocket.read(buffer(readBuf), [&](std::error_code ec, size_t bytes){
            if(!ec) {
                std::cout << "read success with bytes of " << bytes << std::endl;
                std::cout << readBuf << std::endl;
            } else {
                std::cout << ec.message() << std::endl;
            }
        });
        doAccept(acceptor);
    });
}




int main() {

    Reactor reactor;
    Acceptor acceptor(reactor, 12345);
    doAccept(acceptor);

    reactor.run();
    return 0;
}
