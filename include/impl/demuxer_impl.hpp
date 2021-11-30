//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_DEMUXER_IMPL_HPP
#define MEDIA_DEMUXER_IMPL_HPP
#include <basic_demuxer.hpp>
#include <cstdio>

template<typename T>
basic_demuxer<T>::basic_demuxer(){
}

template<typename T>
basic_demuxer<T>::~basic_demuxer(){

}

template<typename T>
void basic_demuxer<T>::input(const void *data, size_t length){
    impl.input(data, length);
}
template<typename T>
void basic_demuxer<T>::set_exception_handler(exception_handler_type func){
    impl.set_exception_handler(std::move(func));
}

template<typename T>
void basic_demuxer<T>::on_write(write_func_type func){
    impl.on_write(std::move(func));
}

#endif //MEDIA_DEMUXER_IMPL_HPP
