//
// Created by liyang on 2/23/20.
//
#include <condition.h>
#include <errno.h>
void init_condition(condition_class * condition,mutex_class * p_mutex)
{
  condition->mutex_ = p_mutex;
  MCHECK(pthread_cond_init(&condition->pcond_,NULL));
}
void destroy_condition(condition_class * condition)
{
    MCHECK(pthread_cond_destroy(&condition->pcond_));
}
void wait_condition(condition_class * condition)
{
    //unbind thread id of mutex
    unassign_holder(condition->mutex_);
    MCHECK(pthread_cond_wait(&condition->pcond_,get_pthread_mutex(condition->mutex_)));
    assign_holder(condition->mutex_);
}
void notify_condition(condition_class * condition)
{
    MCHECK(pthread_cond_signal(&condition->pcond_));
}

void notify_all_condition(condition_class * condition)
{
    MCHECK(pthread_cond_broadcast(&condition->pcond_));
}
/// return true,if waiting time out ,else false
/// \param condition
/// \param seconds
void wait_for_seconds(condition_class * condition, const int seconds)
{
    bool ret;
    struct timespec abstime;
    clock_gettime(CLOCK_REALTIME,&abstime);
    abstime.tv_sec += seconds;
    unassign_holder(condition->mutex_);
    ret = ETIMEDOUT == pthread_cond_timedwait(&condition->pcond_,get_pthread_mutex(condition->mutex_),&abstime);
    assign_holder(condition->mutex_);

}
