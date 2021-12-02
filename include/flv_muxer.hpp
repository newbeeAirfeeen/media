//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_BASIC_MUXER_HPP
#define MEDIA_BASIC_MUXER_HPP
#include <core.hpp>
#include <flv.hpp>
template<typename policy>
class flv_muxer{
public:
    struct impl;
    using muxer_policy = policy;
public:

    flv_muxer(bool video, bool audio);

    ~flv_muxer();

    flv_muxer(const flv_muxer&) = delete;

    flv_muxer& operator = (const flv_muxer& ) = delete;

    void encode(const context& _context, const char* data, size_t len);
public:

    void set_exception_handler(exception_handler_type func);

    void on_flv_header(on_flv_header_func f);

    void on_tag(on_flv_tag_func f);

private:
    impl* impl_ptr;
    muxer_policy p;
};
#endif //MEDIA_BASIC_MUXER_HPP
