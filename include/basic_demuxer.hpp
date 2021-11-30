//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_BASIC_DEMUXER_HPP
#define MEDIA_BASIC_DEMUXER_HPP
#include <core.hpp>
template<typename T>
class basic_demuxer{
public:
    using implement_type = T;
public:
    basic_demuxer();
    ~basic_demuxer();
public:
    void input(const void* data, size_t length);
    void set_exception_handler(exception_handler_type func);
    void on_write(write_func_type func);
private:
    implement_type impl;
    exception_handler_type exception_handler;
    write_func_type write_func;
};

#endif //MEDIA_BASIC_DEMUXER_HPP
