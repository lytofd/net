//
// Created by liyang on 2/28/20.
//
#include <time_stamp.h>
const int k_micro_seconds_persecond = 1000000;
void init_time_stamp_class(time_stamp_class * p_time_stamp, int64_t micro_seconds)
{
    p_time_stamp->micro_seconds_since_epoch_ = micro_seconds;
}

void swap_time_stamp(time_stamp_class * p_this,time_stamp_class * p_that)
{
    // not atomic
    int64_t tmp;
    tmp = p_this->micro_seconds_since_epoch_;
    p_this->micro_seconds_since_epoch_ = p_that->micro_seconds_since_epoch_;
    p_that->micro_seconds_since_epoch_ = tmp;
}

void time_stamp_to_string(time_stamp_class * p_time_stamp,char * buf, int buf_length)
{
    int64_t seconds = p_time_stamp->micro_seconds_since_epoch_ / k_micro_seconds_persecond;
    int64_t  micro_seconds = p_time_stamp->micro_seconds_since_epoch_ % k_micro_seconds_persecond;
    DEBUG("%ld\n",seconds);
    snprintf(buf, buf_length -1 , "%ld.%06ld", seconds,micro_seconds);
    DEBUG("%s\n",buf);

}

time_stamp_class  * now()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    int64_t seconds = tv.tv_sec;
    time_stamp_class  * p_ret = (time_stamp_class*)malloc(sizeof(time_stamp_class));
    init_time_stamp_class(p_ret,seconds * k_micro_seconds_persecond + tv.tv_usec);
    return ;
}

int64_t  micro_seconds_since_epoch(time_stamp_class * p_time_stamp)
{
    return p_time_stamp->micro_seconds_since_epoch_;
}

time_t seconds_since_epoch(time_stamp_class * p_time_stamp)
{
    return (time_t)(p_time_stamp->micro_seconds_since_epoch_/k_micro_seconds_persecond);
}

int time_difference(time_stamp_class * high, time_stamp_class * low)
{
    
    int64_t  diff = high->micro_seconds_since_epoch_ - low->micro_seconds_since_epoch_;
    DEBUG("time diff :%ld\n",diff);
    return (int)(diff/k_micro_seconds_persecond);
}
