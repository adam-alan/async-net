//
// Created by loadstar on 2021/9/11.
//

#ifndef ASYNC_NET__BUFFER_H_
#define ASYNC_NET__BUFFER_H_

#include <iostream>
#include <vector>
#include <string>
#include <array>



class Buffer {
public:

    Buffer(char* begin, char* end)
    : begin_(begin)
    , end_(end){
        for (char* i = begin_; i < end_; ++i) {
            std::cout << *i << std::endl;
        }
    }

    char* data() {
        return begin_;
    }


    size_t size() {
        return end_ - begin_;
    }

    void moveStep(ssize_t step) {
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
    return {buf.data(), buf.data() + N};
}

template<size_t N>
Buffer buffer(char (&buf)[N] ) {
    return {buf, buf + N};
}

#endif //ASYNC_NET__BUFFER_H_
