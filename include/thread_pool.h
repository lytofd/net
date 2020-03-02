//
// Created by liyang on 2/28/20.
//

#ifndef RMMS_THREAD_POOL_H
#define RMMS_THREAD_POOL_H
#include <thread.h>
#include <mutex.h>
#include <condition.h>
#include <list.h>
#include <queue.h>
#include <compiler_def.h>
#include <stdlib.h>
#include <cstl/cvector.h>
#include <cstl/cdeque.h>
#define SETNAME(x) elem##x 
typedef  void (*Task)();

typedef struct thread_pool_
{
    mutex_class mutex_;
    condition_class not_empty_;
    condition_class not_full_;
    char name_[32];
    Task  thread_init_call_back_;
    vector_t * pvect_task;
    deque_t * task_queue_;
    size_t max_queue_size_;
    bool running_;
}thread_pool_class;


void stop_thread_pool(thread_pool_class * p_thread_pool);
void init_thread_pool(thread_pool_class * p_thread_pool,char * name);


void run_in_thread_pool();

void start_thread_pool(thread_pool_class * p_thread_pool, int thread_num);

bool is_full(thread_pool_class * p_thread_pool);

void run_thread_pool(thread_pool_class * p_thread_pool, Task task);


void destroy_thread_pool(thread_pool_class * p_thread_pool);

void set_thread_pool_max_queue_size(thread_pool_class * p_thread_pool,int max_size);


void set_thread_init_call_back(thread_pool_class * p_thread_pool,Task task);

#endif //RMMS_THREAD_POOL_H
