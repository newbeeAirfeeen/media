//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_MULTIPART_MUXER_H
#define MEDIA_MULTIPART_MUXER_H
#include <core.hpp>
#include <basic_muxer.hpp>

template<typename T>
class multipart_muxer : public basic_muxer<T>{
public:
    void input(const basic_stream_context& context,  const void* data, size_t length);
private:
    basic_stream_context context;
};

#endif //MEDIA_MULTIPART_MUXER_H
