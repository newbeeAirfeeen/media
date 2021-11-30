//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_BASIC_MUXER_H
#define MEDIA_BASIC_MUXER_H
#include <basic_muxer.hpp>

template<typename T>
basic_muxer<T>::basic_muxer(){

}

template<typename T>
basic_muxer<T>::~basic_muxer(){

}

template<typename T>
void basic_muxer<T>::input(const basic_stream_context& context,const void* data, size_t length){
    impl.input(context, data, length);
}
template<typename T>
void basic_muxer<T>::set_exception_handler(exception_handler_type func){
    impl.set_exceptioin_handler(std::move(func));
}

template<typename T>
void basic_muxer<T>::on_write(write_func_type func){
    impl.on_write(std::move(func));
}


#endif //MEDIA_BASIC_MUXER_H
