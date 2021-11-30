//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_BASIC_MPEGTS_DEMUXER_IMPL_HPP
#define MEDIA_BASIC_MPEGTS_DEMUXER_IMPL_HPP
#include <functional>
#include <impl/detail/mpeg/mpeg-ts-proto.h>
#include <impl/detail/mpeg/mpeg-ts.h>
#include <core.hpp>
class ts_demuxer_impl
{
public:
    ts_demuxer_impl();

    ~ts_demuxer_impl();

    void input(const void* data, size_t length);

    void set_exception_handler(exception_handler_type exception_handler);

    void on_write(write_func_type write_func);

private:
    ts_demuxer_t* m_demuxer;
    exception_handler_type exception_handler;
    write_func_type write_func;
};

#endif //MEDIA_BASIC_MPEGTS_DEMUXER_IMPL_HPP
