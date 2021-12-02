//
// Created by 沈昊 on 2021/12/2.
//

#ifndef MEDIA_MERGE_POLICY_IMPL_H
#define MEDIA_MERGE_POLICY_IMPL_H
#include <file_merge_policy.hpp>
#include <cmath>
#include <limits>
struct file_merge_policy::impl{
public:
    impl(){
        //首次初始化为0
       time_base = delta_stamp = _last_dts = _last_pts = 0;
    }
    //文件复用不修正pts 与 dts 之间的diff
    void operator()(uint32_t time_base, int64_t& dts_out, int64_t& pts_out){
        if((this->time_base) && (this->time_base) != time_base)
            throw std::logic_error("两次传入的时间基(time_base)不同");
        this->time_base = time_base;
        //初始化
        if(_last_dts == 0 && _last_pts == 0 && delta_stamp == 0){
            _last_dts = dts_out;
            _last_pts = pts_out;
            return;
        }
        if(!delta_stamp){
            //增量时间戳
            delta_stamp = dts_out - _last_dts;
        }
        //已经初始化完成
        //如果dts - _last_dts > 3 * time_base
        //则被认为是新的一个片
        auto duration = dts_out - _last_dts;
        if(duration > (3 * (int64_t)time_base)){
            auto pts_dts_diff = pts_out - dts_out;
            dts_out = abs(_last_dts + delta_stamp) % std::numeric_limits<int64_t>::max();
            pts_out = abs(dts_out + pts_dts_diff) % std::numeric_limits<int64_t>::max();
            //更新解码时间戳
            _last_dts = dts_out;
            _last_pts = pts_out;
        }
    }
private:
    uint32_t time_base;
    /* 增量时间 */
    int64_t delta_stamp;
    /* 上一次dts时间点 */
    int64_t _last_dts;
    /* 上一次pts时间点 */
    int64_t _last_pts;
};


file_merge_policy::file_merge_policy():impl_ptr(nullptr){
    impl_ptr = new impl;
}

file_merge_policy::~file_merge_policy(){
    if(impl_ptr)delete impl_ptr;
}

void file_merge_policy::operator()(uint32_t time_base, int64_t &dts, int64_t &pts) {
    return impl_ptr -> operator() (time_base, dts, pts);
}
#endif //MEDIA_MERGE_POLICY_IMPL_H
