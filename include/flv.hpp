//
// Created by 沈昊 on 2021/12/2.
//

#ifndef MEDIA_FLV_HPP
#define MEDIA_FLV_HPP
#include <functional>
#define FLV_TAG_HEADER_LENGTH 11
#define FLV_PREVIOUS_TAG_LENGTH 4
using on_flv_header_func = std::function<void(int version, bool v, bool a, const char*data, size_t len)>;
using on_flv_tag_func = std::function<void(int tag_type, uint32_t timestamp, const char*data, size_t len)>;
#endif //MEDIA_FLV_HPP
