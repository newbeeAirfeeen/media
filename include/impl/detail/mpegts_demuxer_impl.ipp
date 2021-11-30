//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_MPEGTS_DEMUXER_IMPL_IPP
#define MEDIA_MPEGTS_DEMUXER_IMPL_IPP
#include <cstdio>
#include <impl/mpegts_demuxer_impl.hpp>
#include <impl/codec_helper.hpp>
static constexpr const int mpegts_time_base = 90000;
static Codec mpegts_mapping_codec(int codec_id){
    switch(codec_id){
        case PSI_STREAM_H264: return Codec::H264_AnnexB;
        case PSI_STREAM_H265: return Codec::H265;
        case PSI_STREAM_AAC: return Codec::AAC_ADTS;
        case PSI_STREAM_MP3: return Codec::MP3;
        default: return  Codec::unknown;
    }
}

ts_demuxer_impl::ts_demuxer_impl():m_demuxer(nullptr){
    exception_handler = [](const std::logic_error& mfe){
        fprintf(stderr, "%s\n", mfe.what());
    };
    write_func = [](const basic_stream_context& context, const void* data, size_t bytes) -> int{
        return 0;
    };
    m_demuxer = ts_demuxer_create([](void* param, int program, int stream, int codecid, int flags, int64_t pts, int64_t dts, const void* data, size_t bytes) -> int{
        ts_demuxer_impl* _this = static_cast<ts_demuxer_impl*>(param);
        Codec codec = mpegts_mapping_codec(codecid);
        if( codec == Codec::unknown)
            throw std::logic_error("unkown codec id, mpegts for this muxer not support");
        basic_stream_context context{codec, mpegts_time_base, dts, pts};
        _this->write_func(context, data, bytes);
        return 0;
    }, this);
}

ts_demuxer_impl::~ts_demuxer_impl(){
    ts_demuxer_destroy(m_demuxer);
}

void ts_demuxer_impl::input(const void* data, size_t length){
    if( length % TS_PACKET_SIZE != 0){
        throw std::logic_error("mpegts packet size not 188 bytes length or 188 times length");
    }
    const char* begin = static_cast<const char*>(data);
    const char* end = begin + length;
    while(begin < end){
        int ret = ts_demuxer_input(m_demuxer, (const uint8_t*)begin, TS_PACKET_SIZE);
        if( ret < 0){
            throw std::logic_error("mpegts parse error");
        }
        begin += TS_PACKET_SIZE;
    }
}

void ts_demuxer_impl::set_exception_handler(exception_handler_type exception_handler){
    this->exception_handler = std::move(exception_handler);
}

void ts_demuxer_impl::on_write(write_func_type write_func){
    this->write_func = (std::move(write_func));
}
#endif //MEDIA_BASIC_MPEGTS_DEMUXER_IMPL_HPP
