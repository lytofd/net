//
// Created by liyang on 2/23/20.
//

#ifndef RMMS_COUNT_DOWN_LATCH_H
#define RMMS_COUNT_DOWN_LATCH_H
#include <condition.h>
#include <mutex.h>
typedef struct count_down_latch_
{
    mutex_class  mutex_;
    condition_class condition_;
    int count_;
}count_down_latch_class;

void init_count_down_latch(count_down_latch_class * p_count_down_latch, const int count);

void wait_count_down(count_down_latch_class * p_count_down_latch);

void count_down(count_down_latch_class * p_count_down_latch);

int get_count(count_down_latch_class * p_count_down_latch);

#endif //RMMS_COUNT_DOWN_LATCH_H
