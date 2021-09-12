//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__BUFFER_H_
#define ASYNC_NET__BUFFER_H_


#include <vector>
#include <string>
#include <array>



class Buffer {
public:

    Buffer(char* begin, char* end)
    : begin_(begin)
    , end_(end){

    }

    char* data() {
        return begin_;
    }


    size_t size() {
        return end_ - begin_;
    }

    void moveStep(int step) {
        begin_ += step;
    }


private:
    char* begin_;
    char* end_;
};

Buffer buffer(std::vector<char> buf);

Buffer buffer(std::string buf);

template<size_t N>
Buffer buffer(std::array<char, N> buf) {
    return Buffer{buf.data(), buf.data() + N};
}

template<size_t N>
Buffer buffer(char (&buf)[N] ) {
    return Buffer{buf, buf + N};
}

#endif //ASYNC_NET__BUFFER_H_
