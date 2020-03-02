//
// Created by liyang on 2/23/20.
//
#include <count_down_latch.h>
void init_count_down_latch(count_down_latch_class * p_count_down_latch, const int count)
{
    p_count_down_latch->count_ = count;
    init_mutex(&p_count_down_latch->mutex_);
    init_condition(&p_count_down_latch->condition_,&p_count_down_latch->mutex_);
    p_count_down_latch->count_ = count;
}

void wait_count_down(count_down_latch_class * p_count_down_latch)
{
    lock(&p_count_down_latch->mutex_);
    while(p_count_down_latch->count_ >0)
    {
        wait_condition(&p_count_down_latch->condition_);
    }
    unlock(&p_count_down_latch->mutex_);
}

void count_down(count_down_latch_class * p_count_down_latch)
{
    lock(&p_count_down_latch->mutex_);
    --p_count_down_latch->count_;
    if(p_count_down_latch->count_ == 0)
    {
        notify_all_condition(&p_count_down_latch->condition_);
    }
    unlock(&p_count_down_latch->mutex_);
}

int get_count(count_down_latch_class * p_count_down_latch)
{
    lock(&p_count_down_latch->mutex_);
    unlock(&p_count_down_latch->mutex_);
    //TODO
    return p_count_down_latch->count_;

}

