#include <iostream>
#include <thread>
#include "StreamSocket.h"







int main() {

    Reactor reactor;
    StreamSocket socket(reactor);
    socket.bind(12345);
    std::cout << "bind succ" << std::endl;
    socket.listen();
    std::cout << "listen succ" << std::endl;
    reactor.run();

    return 0;
}
