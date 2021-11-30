//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_CORE_HPP
#define MEDIA_CORE_HPP
#include <functional>
#include <impl/codec_helper.hpp>
struct basic_stream_context{
    Codec codec;
    int time_base;
    int64_t dts;
    int64_t pts;
};
using exception_handler_type = std::function<void(const std::logic_error& e)>;
using write_func_type = std::function<void(const basic_stream_context& context, const void* data, size_t bytes)>;
#endif //MEDIA_CORE_H
