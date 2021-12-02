//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_MPEGTS_DEMUXER_IMPL_IPP
#define MEDIA_MPEGTS_DEMUXER_IMPL_IPP
#include <cstdio>
#include <ts_demuxer.hpp>
#include "detail/mpeg-ts.h"
#include "detail/mpeg-ts-proto.h"
static code_type get_ts_codec(int codec){
    switch(codec){
        case PSI_STREAM_H264: return code_type::H264_AnnexB;
        case PSI_STREAM_H265: return code_type::H265;
        case PSI_STREAM_AAC: return code_type::AAC_ADTS;
        case PSI_STREAM_MP3: return code_type::MP3;
        default: return code_type::unknown;
    }
}

struct ts_demuxer::impl{

public:
    using native_handle_type = int;
    static constexpr const int time_base = 90000;
public:
    impl():m_demuxer(nullptr){
        init();
    }
    ~impl(){
        if(m_demuxer)ts_demuxer_destroy(m_demuxer);
    }
    void decode(const void* data, size_t length){
        try{
            if( length % TS_PACKET_SIZE != 0)throw std::logic_error("输入的mpegts的包的长度必须是188字节或188字节的倍数");
            const char* begin = static_cast<const char*>(data);
            const char* end = begin + length;
            while(begin < end){
                int ret = ts_demuxer_input(m_demuxer, (const uint8_t*)begin, TS_PACKET_SIZE);
                if( ret < 0){
                    throw std::logic_error("mpegts解复用失败");
                }
                begin += TS_PACKET_SIZE;
            }
        }catch(const std::logic_error& e){
            exception_handler(e);
        }
    }
    void set_exception_handler(exception_handler_type func){
        this->exception_handler = std::move(func);
    }
    void set_output(ts_output_func_type f){
        this->output_func = std::move(f);
    }
private:
    void init(){
        output_func = [](const context&, const char*, size_t){};
        exception_handler = [](const std::logic_error& e){ throw e;};
        m_demuxer = ts_demuxer_create([](void* param, int program, int stream, int codecid,
                int flags, int64_t pts, int64_t dts, const void* data, size_t bytes) -> int{
            impl* _this = static_cast<impl*>(param);
            context st = {get_ts_codec(codecid), time_base, dts, pts};
            _this->output_func(st, (const char*)data, bytes);
            return 0;
        }, this);
    }
private:
    ts_demuxer_t* m_demuxer;
    exception_handler_type exception_handler;
    ts_output_func_type output_func;
};


ts_demuxer::ts_demuxer():impl_ptr(nullptr){
    this->impl_ptr = new impl();
}

ts_demuxer::~ts_demuxer(){
    if(impl_ptr)delete impl_ptr;
}

void ts_demuxer::decode(const void* data, size_t len){
    impl_ptr->decode(data, len);
}

void ts_demuxer::set_exception_handler(exception_handler_type exception_handler){
    impl_ptr -> set_exception_handler(std::move(exception_handler));
}

void ts_demuxer::set_output(ts_output_func_type f){
    impl_ptr ->set_output(std::move(f));
}



#endif //MEDIA_BASIC_MPEGTS_DEMUXER_IMPL_HPP
