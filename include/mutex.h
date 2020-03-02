//
// Created by liyang on 2/20/20.
//
#include <assert.h>
#include <pthread.h>
#include <current_thread.h>
#include <device_status.h>
#ifndef RMMS_MUTEX_H
#define RMMS_MUTEX_H
#define MCHECK(ret) ({ __typeof__ (ret) errnum = (ret);         \
                       if (__builtin_expect(errnum != 0, 0))    \
                         __assert_perror_fail (errnum, __FILE__, __LINE__, __func__);})
typedef  struct _mutex
{
    pthread_mutex_t mutex_;
    pid_t holder_;
}mutex_class;
void init_mutex(mutex_class * p_mutex);

void destroy_mutex(mutex_class * p_mutex);


void assign_holder(mutex_class * p_mutex);


void unassign_holder(mutex_class * p_mutex);


void lock(mutex_class * p_mutex);



void unlock(mutex_class * p_mutex) ;


bool is_locked_by_current_thread(mutex_class * p_mutex);


void assert_locked(mutex_class * p_mutex);


pthread_mutex_t * get_pthread_mutex(mutex_class * p_mutex);





#endif //RMMS_MUTEX_H
