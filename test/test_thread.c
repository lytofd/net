//
// Created by liyang on 2/19/20.
//

#include <string.h>
#include <stdio.h>
#include <thread.h>
const int max_thread_count = 10;
int count = 0;
void thread_fun1()
{
    DEBUG("tid = %d\n",tid());
    int i =0;
    for(i = 0;i<1000000;i++)
    {
      count += 1;
    }
    DEBUG("tid:%d,count::%d,thread_name:%s\n",tid(),count,name());
}

void test_multi_task()
{
    thread_class thread_array[max_thread_count];
    int index = 0;
    for(index = 0;index<max_thread_count;index++)
    {
        char name[32];
        snprintf(name,sizeof(name),"work thread %d",index);
        DEBUG("name:%s\n",name);
        init_thread(&thread_array[index],thread_fun1,name);
        start(&thread_array[index]);
    }
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
    DEBUG("pid = %d, tid = %d  \n",getpid(),tid());

    thread_class thread_obj1;
    /*init_thread(&thread_obj1,thread_fun1,NULL);
    start(&thread_obj1);
    join(&thread_obj1);
    destory_thread(&thread_obj1);
    */
    test_multi_task();

}
