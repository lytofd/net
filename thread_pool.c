//
// Created by liyang on 2/28/20.
//
#include <thread_pool.h>
#include <string.h>
thread_pool_class * p_global_thread_pool = NULL;
void init_thread_pool(thread_pool_class * p_thread_pool,char * name)
{
    int name_size = strlen(name);

    type_register(thread_class, NULL, NULL, NULL, NULL);
    p_thread_pool->pvect_task = create_vector(thread_class);
    vector_init(p_thread_pool->pvect_task);

    type_register(Task, NULL, NULL, NULL, NULL);
    p_thread_pool->task_queue_ = create_deque(Task);
    deque_init(p_thread_pool->task_queue_);

    init_mutex(&p_thread_pool->mutex_);
    init_condition(&p_thread_pool->not_empty_,&p_thread_pool->mutex_);
    init_condition(&p_thread_pool->not_full_,&p_thread_pool->mutex_);
    snprintf(p_thread_pool->name_,name_size,"%s",name);
    p_thread_pool->max_queue_size_ = 0;
    p_thread_pool->running_ = false;
    p_thread_pool->thread_init_call_back_ = NULL;
    p_global_thread_pool = p_thread_pool;
}

void stop_thread_pool(thread_pool_class * p_thread_pool)
{
    lock(&p_thread_pool->mutex_);
    p_thread_pool->running_ = false;
    p_global_thread_pool->running_ = false;
    DEBUG("OVER\n")
    notify_all_condition(&p_thread_pool->not_full_);
    notify_all_condition(&p_thread_pool->not_empty_);
    unlock(&p_thread_pool->mutex_);
    /// destory thread list
    int index = 0;
    int list_size = vector_size(p_thread_pool->pvect_task);
    DEBUG("destroying %d threads\n",list_size);
    for(;index < list_size;index ++)
    {
        thread_class thread = *(thread_class *)vector_at(p_thread_pool->pvect_task,index);
        join(&thread);
        destory_thread(&thread);
    }
    /// destroy condition && mutex
    destroy_condition(&p_thread_pool->not_empty_);
    destroy_condition(&p_thread_pool->not_full_);
    destroy_mutex(&p_thread_pool->mutex_);
    vector_destroy(p_thread_pool->pvect_task);
   // deque_destroy(p_thread_pool->task_queue_);
    p_global_thread_pool = NULL;


}
Task take_from_work_queue(thread_pool_class * p_thread_pool)
{
    lock(&p_thread_pool->mutex_);
    while(!deque_size(p_thread_pool->task_queue_)&&p_thread_pool->running_)
    {
        
        wait_condition(&p_thread_pool->not_empty_);
    }
    DEBUG("receive signal\n");
    Task task;
    int queue_size = deque_size(p_thread_pool->task_queue_);
    if(queue_size > 0)
    {
        
        task = *(Task *)deque_front(p_thread_pool->task_queue_);
        deque_pop_front(p_thread_pool->task_queue_);
        if(p_thread_pool->max_queue_size_ > 0)
        {
            notify_condition(&p_thread_pool->not_full_);
        }
    }
    else
    {
      ERROR("task queue has no elem\n");
      task = NULL;
    }
    unlock(&p_thread_pool->mutex_);
    return task;
}
void run_in_thread_pool()
{
    if(p_global_thread_pool->thread_init_call_back_)
    {
        DEBUG("running thread_init_call_back_\n");
        p_global_thread_pool->thread_init_call_back_();
    }
    while(p_global_thread_pool->running_)
    {
	DEBUG("task looping\n");
        Task task = take_from_work_queue(p_global_thread_pool);
        if(task)
        {
            task();
        }
    }
    DEBUG("thread %d exit\n",tid());
}
void start_thread_pool(thread_pool_class * p_thread_pool, int thread_num)
{

    p_thread_pool->running_ = true;
    int index ;
    for(index = 0;index<thread_num;index++)
    {
        char name_id[32];
        snprintf(name_id,sizeof(name_id),"%s-%d",p_thread_pool->name_,index);
        thread_class thread;

        init_thread(&thread,run_in_thread_pool,name_id);
        start(&thread);
        vector_push_back(p_thread_pool->pvect_task,&thread);
    }
    int list_length = vector_size(p_thread_pool->pvect_task);
    if(thread_num == 0 && p_thread_pool->thread_init_call_back_)
    {
        p_thread_pool->thread_init_call_back_();
    }
}
bool is_full(thread_pool_class * p_thread_pool)
{
  if(p_thread_pool->max_queue_size_ > 0 && deque_size(p_thread_pool->task_queue_)>= p_thread_pool->max_queue_size_)
  {
      return true;
  }
    return false;
}
void run_thread_pool(thread_pool_class * p_thread_pool, Task task)
{
    int thread_list_length = vector_size(p_thread_pool->pvect_task);
    if(!thread_list_length)
    {
        task();
    }
    lock(&p_thread_pool->mutex_);
    while(is_full(p_thread_pool))
    {
        wait_condition(&p_thread_pool->not_full_);
    }
    deque_push_back(p_thread_pool->task_queue_,&task);
    notify_condition(&p_thread_pool->not_empty_);
    unlock(&p_thread_pool->mutex_);
}

void destroy_thread_pool(thread_pool_class * p_thread_pool)
{
    if(p_thread_pool->running_)
    {
        stop_thread_pool(p_thread_pool);
    }
}
void set_thread_pool_max_queue_size(thread_pool_class * p_thread_pool,int max_size)
{
    p_thread_pool->max_queue_size_ = max_size;
}

void set_thread_init_call_back(thread_pool_class * p_thread_pool,Task task)
{
    p_thread_pool->thread_init_call_back_ = task;
}
