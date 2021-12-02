//
// Created by 沈昊 on 2021/12/2.
//

#ifndef MEDIA_MPEGTS_H
#define MEDIA_MPEGTS_H
#include <core.hpp>
using ts_output_func_type = std::function<void(const context&, const char*, size_t)>;
#endif //MEDIA_MPEGTS_H
