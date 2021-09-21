//#include <iostream>
//#include <thread>
//#include <string>
//#include <queue>
//#include <functional>

#include "Reactor.h"
#include "Acceptor.h"

class Conn:public std::enable_shared_from_this<Conn>{
public:
    explicit Conn(std::shared_ptr<ReadWriteSocket> readWriteSocket):
    readWriteSocket_(readWriteSocket){
        readBuf[0] = '\0';
        readBuf[1] = '\0';
        readBuf[2] = '\0';
        readBuf[3] = '\0';
        readBuf[4] = '\0';
        readBuf[5] = '\0';


        writeBuf[0] = 'h';
        writeBuf[1] = 'e';
        writeBuf[2] = 'l';
        writeBuf[3] = 'l';
        writeBuf[4] = 'o';
        writeBuf[5] = '\0';
    }


    void start() {
        auto self = shared_from_this();

        readWriteSocket_->write(buffer(writeBuf), [this, self](std::error_code ec, size_t bytes){
            if(!ec) {
                std::cout << "write success with bytes of " << bytes << std::endl;
                std::cout << writeBuf << std::endl;

            }
        });

        readWriteSocket_->read(buffer(readBuf), [this, self] (std::error_code ec, size_t bytes){
            if(!ec) {
                std::cout << "read success with bytes of " << bytes << std::endl;
                std::cout << readBuf << std::endl;
            } else {
                std::cout << ec.message() << std::endl;
            }
        });

    }

private:
    char writeBuf[6];
    char readBuf[6];
    std::shared_ptr<ReadWriteSocket> readWriteSocket_;
};


void doAccept(Acceptor& acceptor) {
    acceptor.accept([&](std::error_code ec, std::shared_ptr<ReadWriteSocket> streamSocket){


        std::make_shared<Conn>(streamSocket)->start();


        doAccept(acceptor);
    });
}


struct Data{
    std::queue<std::function<void()>> funcs;
};



struct Foo {
    Foo(Data& data)
    :data_(data){

    }

    void operator()() {
        std::cout << num << std::endl;
        num += 1;
        data_.funcs.push(*this);
    }
    int num = 0;
    Data& data_;
};



int main() {
//
    Reactor reactor;
    Acceptor acceptor(reactor, 12345);
    doAccept(acceptor);
    reactor.run();
//    Data data;
//    Foo foo(data);
//    foo();
//    while(!data.funcs.empty()) {
//        data.funcs.front()();
//        data.funcs.pop();
//    }
    return 0;
}
