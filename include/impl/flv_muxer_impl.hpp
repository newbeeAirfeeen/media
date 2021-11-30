//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_BASIC_FLV_MUXER_IMPL_H
#define MEDIA_BASIC_FLV_MUXER_IMPL_H
#include <core.hpp>
#include <impl/detail/flv/flv-muxer.h>
class flv_muxer_impl{
public:
    flv_muxer_impl();

    ~flv_muxer_impl();

    void input(const basic_stream_context& context, const void* data, size_t length);

    void set_exception_handler(exception_handler_type exception_handler);

    void on_write(write_func_type write_func);

private:
    flv_muxer_t * m_muxer;
    exception_handler_type exception_handler;
    write_func_type write_func;
};
#endif //MEDIA_BASIC_FLV_MUXER_IMPL_H
