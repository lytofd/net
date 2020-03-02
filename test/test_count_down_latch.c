//
// Created by liyang on 2/23/20.
//

#include <count_down_latch.h>
#include <string.h>
#include <stdio.h>
#include <thread.h>

count_down_latch_class latch;
int max_thread_count = 10;
int latch_num = 1;
thread_class thread_array[10];

void thread_fun1()
{
    sleep(10);
    wait_count_down(&latch);
    DEBUG("tid=%d,  started\n",tid());
    DEBUG("tid=%d,  stoped\n",tid());

}

void multi_task_with_condition()
{
    // initing count_down_latch
    init_count_down_latch(&latch,latch_num);
    int index = 0;
    for(index = 0;index<max_thread_count;index++)
    {
        char name[32];
        snprintf(name,sizeof(name),"work thread %d",index);
        init_thread(&thread_array[index],thread_fun1,name);
        start(&thread_array[index]);
    }

}
void count_down_latch()
{
    count_down(&latch);
}
void join_all()
{
    int index;
    for(index = 0;index<max_thread_count;index++)
    {
        join(&thread_array[index]);
    }
    for(index = 0;index<max_thread_count;index++)
    {
        destory_thread(&thread_array[index]);
    }
}
int main()
{
    DEBUG("pid=%d,tid=%d\n",getpid(),tid());
    multi_task_with_condition();
    sleep(5);
    count_down_latch();
    join_all();


}
