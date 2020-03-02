//
// Created by liyang on 2/28/20.
//

#ifndef RMMS_TIME_STAMP_H
#define RMMS_TIME_STAMP_H
#include <sys/time.h>
#include <stdio.h>
#include <inttypes.h>
#include<stdlib.h>

#include<string.h>
#include <log.h>
typedef  struct time_stamp_
{
   int64_t micro_seconds_since_epoch_;
}time_stamp_class;

void init_time_stamp_class(time_stamp_class * p_time_stamp, int64_t micro_seconds);


void swap_time_stamp(time_stamp_class * p_this,time_stamp_class * p_that);


void time_stamp_to_string(time_stamp_class * p_time_stamp,char * buf,int buf_length);


time_stamp_class  *  now();

int time_difference(time_stamp_class * high, time_stamp_class * low);



int64_t  micro_seconds_since_epoch(time_stamp_class * p_time_stamp);
time_t seconds_since_epoch(time_stamp_class * p_time_stamp);

 #endif//RMMS_TIME_STAMP_H
