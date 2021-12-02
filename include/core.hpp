//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_CORE_HPP
#define MEDIA_CORE_HPP
#include <functional>
enum code_type{
    unknown,
    H264_AVC,
    H264_AnnexB,
    H265,
    AAC_ADTS,
    AAC_ASC,
    MP3,
};

struct context{
    code_type codec_type;
    int time_base;
    int64_t dts;
    int64_t pts;
};
using exception_handler_type = std::function<void(const std::logic_error& e)>;
#endif //MEDIA_CORE_H
