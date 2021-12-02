//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_FLV_MUXER_IMPL_IPP
#define MEDIA_FLV_MUXER_IMPL_IPP
#include <flv_muxer.hpp>
#include <impl/flv/detail/flv-proto.h>
#include <impl/flv/detail/flv-muxer.h>
#include <impl/flv/detail/flv-writer.h>
#include <impl/flv/detail/flv-header.h>
template<typename T>
struct flv_muxer<T>::impl{
public:
    using native_handle_type = int;
    static constexpr const int time_base = 1000;
    static constexpr const int version = 1;
public:
    impl(bool has_video, bool has_audio):header_written(false), has_audio(has_audio), has_video(has_video){
        init(has_video, has_audio);
    }
    ~impl(){
        if(m_muxer)flv_muxer_destroy(m_muxer);
    }
public:
    void encode(const context& _context, const char* data, size_t len){
        try{
            native_handle_type ret = 0;
            auto dts = _context.dts * time_base / _context.time_base;
            auto pts = _context.pts * time_base / _context.time_base;
            switch (_context.codec_type) {
                case H264_AnnexB:
                case H264_AVC:
                    ret = flv_muxer_avc(m_muxer, data, len, pts, dts);
                    break;
                case H265:
                    ret = flv_muxer_hevc(m_muxer, data, len, pts, dts);
                    break;
                case MP3:
                    ret = flv_muxer_mp3(m_muxer, data, len, pts, dts);
                    break;
                case AAC_ADTS:
                    ret = flv_muxer_aac(m_muxer, data, len, pts, dts);
                    break;
                default:throw std::logic_error("flv复用器不支持当前编码类型或当前版本不支持");
            }
        }catch(const std::logic_error& e){
            exception_handler(e);
        }
    }

    void set_exception_handler(exception_handler_type func){
        this->exception_handler = std::move(func);
    }

    void on_flv_header(on_flv_header_func f){
        this->header_func = std::move(f);
    }

    void on_tag(on_flv_tag_func f){
        this->tag_func = std::move(f);
    }
private:
    void init(bool has_video, bool has_audio){
        header_func = [](int version, bool v, bool a, const char*data, size_t len){};
        tag_func = [](int tag_type, uint32_t timestamp, const char*data, size_t len){};
        exception_handler = [](const std::logic_error& e){
            throw e;
        };
        m_muxer = flv_muxer_create([](void* param, int type, const void* data,
                                      size_t bytes, uint32_t timestamp) -> int{
            impl* _this = static_cast<impl*>(param);
            /* 写入flv头*/
            _this->write_header();
            /* 写入tag */
            _this->write_tag(type, data, bytes, timestamp);
            return 0;
        }, this);

    }
    void write_header(){
        if(header_written)return;
        char header[13] = {0};
        header[0] = 'F';
        header[1] = 'L';
        header[2] = 'V';
        header[3] = (char)version;
        header[4] = ((has_audio ? 1 : 0) << 2) | (has_video ? 1 : 0);
        header[8] = 9;
        header_func(version, has_video, has_audio, header, 13);
        header_written = true;
    }
    void write_tag(int type, const void* data, size_t bytes, uint32_t timestamp){
        char buf[FLV_TAG_HEADER_LENGTH + FLV_PREVIOUS_TAG_LENGTH] = {0};
        struct flv_tag_header_t tag;
        memset(&tag, 0, sizeof(tag));
        tag.size = (int)bytes;
        tag.type = (uint8_t)type;
        tag.timestamp = timestamp;

        native_handle_type ret = flv_tag_header_write(&tag, (uint8_t*)buf, FLV_TAG_HEADER_LENGTH);
        if( ret < 0)throw std::logic_error("flv写入tag头失败");

        ret = flv_tag_size_write((uint8_t*)buf + FLV_TAG_HEADER_LENGTH, 4,
                                 (uint32_t)bytes + FLV_TAG_HEADER_LENGTH);
        if( ret < 0)throw std::logic_error("flv tag size写入失败");
        std::string tag_buf;
        /* write tag_header */
        tag_buf.append(buf, FLV_TAG_HEADER_LENGTH);
        /* write tag body */
        tag_buf.append((const char*)data, bytes);
        /* write previous tag length 4 */
        tag_buf.append(buf + FLV_TAG_HEADER_LENGTH, FLV_PREVIOUS_TAG_LENGTH);
        tag_func(type, timestamp, tag_buf.data(), tag_buf.size());
    }
private:
    flv_muxer_t* m_muxer;

    on_flv_header_func header_func;

    on_flv_tag_func tag_func;

    exception_handler_type exception_handler;
    /* flv头是否输出*/
    bool header_written;
    /* 是否具有音频流 */
    bool has_audio;
    /* 是否具有视频流 */
    bool has_video;
};


template<typename Policy>
flv_muxer<Policy>::flv_muxer(bool video, bool audio):impl_ptr(nullptr){
    this->impl_ptr = new impl(video, audio);
}

template<typename Policy>
flv_muxer<Policy>::~flv_muxer(){
    if(impl_ptr)delete impl_ptr;
}

template<typename Policy>
void flv_muxer<Policy>::encode(const context& _context, const char* data, size_t len){
    context _revise_context = _context;
    p.operator()(_revise_context.time_base, std::ref(_revise_context.dts), std::ref(_revise_context.pts));
    impl_ptr->encode(_revise_context, data, len);
}

template<typename Policy>
void flv_muxer<Policy>::set_exception_handler(exception_handler_type exception_handler){
    impl_ptr -> set_exception_handler(std::move(exception_handler));
}

template<typename Policy>
void flv_muxer<Policy>::flv_muxer::on_flv_header(on_flv_header_func f){
    impl_ptr -> on_flv_header(std::move(f));
}

template<typename Policy>
void flv_muxer<Policy>::on_tag(on_flv_tag_func f){
    impl_ptr -> on_tag(std::move(f));
}



#endif //MEDIA_FLV_MUXER_IMPL_IPP
