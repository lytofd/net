//
// Created by liyang on 2/23/20.
//

#ifndef RMMS_CONDITION_H
#define RMMS_CONDITION_H

#include <mutex.h>
#include <pthread.h>
typedef struct condition_class_
{
   mutex_class * mutex_;
   pthread_cond_t pcond_;
}condition_class;

void init_condition(condition_class * condition,mutex_class * p_mutex);
void destroy_condition(condition_class * condition);
void wait_condition(condition_class * condition);
void notify_condition(condition_class * condition);
void notify_all_condition(condition_class * condition);
void wait_for_seconds(condition_class * condition, const int seconds);

#endif //RMMS_CONDITION_H
