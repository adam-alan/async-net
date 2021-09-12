//
// Created by loadstar on 2021/9/12.
//


#include "Buffer.h"

Buffer buffer(std::vector<char> buf){
    return {std::data(buf), std::data(buf) + std::size(buf)};
}

Buffer buffer(std::string buf){
    return {std::data(buf), std::data(buf) + std::size(buf)};
}


