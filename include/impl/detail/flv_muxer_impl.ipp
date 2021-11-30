//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_FLV_MUXER_IMPL_IPP
#define MEDIA_FLV_MUXER_IMPL_IPP
#include <impl/flv_muxer_impl.hpp>
#include <impl/detail/flv/flv-proto.h>
#include <impl/detail/flv/flv-reader.h>
static constexpr const int flv_time_base = 1000;

flv_muxer_impl::flv_muxer_impl():m_muxer(nullptr){
    m_muxer = flv_muxer_create([](void* param, int type, const void* data, size_t bytes, uint32_t timestamp) -> int{
        flv_muxer_impl* _this = static_cast<flv_muxer_impl*>(param);
        const char tag = ((const char*)data)[0];
        basic_stream_context context{unknown, flv_time_base, timestamp, timestamp};
        _this->write_func(context, data, bytes);
        return 0;
    }, this);
}

flv_muxer_impl::~flv_muxer_impl(){
    flv_muxer_destroy(m_muxer);
}

void flv_muxer_impl::input(const basic_stream_context& context, const void* data, size_t length){
    //default one tag parser
    int64_t dts = flv_time_base * context.dts / context.time_base;
    int64_t pts = flv_time_base * context.pts / context.time_base;
    int ret = 0;
    try{
        switch(context.codec)
        {
            case Codec::AAC_ADTS:
                ret = flv_muxer_aac(m_muxer, data, length, pts, dts);
                break;
            case Codec::H264_AnnexB:
            case Codec::H264_AVC:
                ret = flv_muxer_avc(m_muxer, data, length, pts, dts);
                break;
            case Codec::H265:
                ret = flv_muxer_hevc(m_muxer, data, length, pts, dts);
                break;
            case Codec::MP3:
                ret = flv_muxer_mp3(m_muxer, data, length, pts , dts);
                break;
            default:
                throw std::logic_error("flv muxer error: unkown codec type");
        }
        if(ret != 0)
            throw std::logic_error("flv muxer unknown error");
    }catch(const std::logic_error& e){
        exception_handler(e);
    }
}

void flv_muxer_impl::set_exception_handler(exception_handler_type exception_handler){
    this->exception_handler = std::move(exception_handler);
}

void flv_muxer_impl::on_write(write_func_type write_func){
    this->write_func = std::move(write_func);
}
#endif //MEDIA_FLV_MUXER_IMPL_IPP
