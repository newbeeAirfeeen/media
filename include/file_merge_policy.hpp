//
// Created by 沈昊 on 2021/12/2.
//

#ifndef MEDIA_MERGE_POLICY_H
#define MEDIA_MERGE_POLICY_H

#include <iostream>
class file_merge_policy{
public:
    struct impl;
public:
    file_merge_policy();
    ~file_merge_policy();
    void operator()(uint32_t time_base, int64_t& dts, int64_t& pts);
private:
    impl* impl_ptr;
};


#endif //MEDIA_MERGE_POLICY_H
