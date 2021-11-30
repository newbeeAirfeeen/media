//
// Created by 沈昊 on 2021/11/30.
//

#ifndef MEDIA_MEDIA_HPP
#define MEDIA_MEDIA_HPP
#include <impl/muxer_impl.hpp>
#include <impl/demuxer_impl.hpp>
#include <impl/detail/mpegts_demuxer_impl.ipp>
#include <impl/detail/flv_muxer_impl.ipp>
using basic_ts_demuxer = basic_demuxer<ts_demuxer_impl>;
using basic_flv_muxer  = basic_muxer<flv_muxer_impl>;
#endif //MEDIA_MEDIA_H
