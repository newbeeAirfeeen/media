//
// Created by 沈昊 on 2021/12/2.
//

#ifndef MEDIA_MUXER_POLICY_H
#define MEDIA_MUXER_POLICY_H


class default_policy{
public:
    void operator()(uint32_t time_base, int64_t& dts, int64_t& pts){}
};



#endif //MEDIA_MUXER_POLICY_H
