//
// Created by liyang on 2/20/20.
//
#include <mutex.h>


void init_mutex(mutex_class * p_mutex)
{
    p_mutex->holder_ = 0;
    MCHECK(pthread_mutex_init(&p_mutex->mutex_,NULL));

}
void destroy_mutex(mutex_class * p_mutex)
{
    MCHECK(pthread_mutex_destroy(&p_mutex->mutex_));

}

void assign_holder(mutex_class * p_mutex)
{
    p_mutex->holder_ = tid();

}

void unassign_holder(mutex_class * p_mutex)
{
    p_mutex->holder_ = 0;

}

void lock(mutex_class * p_mutex)
{
    MCHECK(pthread_mutex_lock(&p_mutex->mutex_));
    assign_holder(p_mutex);

}


void unlock(mutex_class * p_mutex)
{
    unassign_holder(p_mutex);
    MCHECK(pthread_mutex_unlock(&p_mutex->mutex_));

}

bool is_locked_by_current_thread(mutex_class * p_mutex)
{
    if(tid() == p_mutex->holder_)
        return true;
    return false;
}

void assert_locked(mutex_class * p_mutex)
{
    assert(is_locked_by_current_thread(p_mutex));
}

pthread_mutex_t * get_pthread_mutex(mutex_class * p_mutex)
{
    return &p_mutex->mutex_;
}
