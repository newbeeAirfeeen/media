//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_BASIC_DEMUXER_HPP
#define MEDIA_BASIC_DEMUXER_HPP
#include <mpegts.h>
class ts_demuxer{
public:
    struct impl;
public:
    ts_demuxer();
    ts_demuxer(const ts_demuxer&) = delete;
    ts_demuxer& operator = (const ts_demuxer&) = delete;
    ~ts_demuxer();
public:
    void decode(const void* data, size_t length);
    void set_exception_handler(exception_handler_type func);
    void set_output(ts_output_func_type);
private:
    impl* impl_ptr;
};

#endif //MEDIA_BASIC_DEMUXER_HPP
