#include <string.h>
#include <stdio.h>
#include <thread.h>
#include <mutex.h>

int g_count = 0;
int k_inner_loop = 10;
int max_thread_count = 10;
mutex_class mutex;
int foo()
{
    mutex.holder_ = 0;
    init_mutex(&mutex);
    DEBUG("Initing succeful\n");
    if(is_locked_by_current_thread(&mutex))
    {
        DEBUG("foo function failed\n");
        return -1;
    }
    ++g_count;
    return 0;
}


void thread_fun1()
{
   lock(&mutex);
   DEBUG("tid = %d\n",tid());
    int i =0;
    DEBUG("%d begin\n",tid());
    for(i = 0;i<1000000;i++)
    {
      g_count += 1;
    }
    DEBUG("%d end\n",tid());
    DEBUG("%d:%d\n",tid(),g_count);
    unlock(&mutex);
}

void test_multi_task_with_guard()
{
    thread_class thread_array[max_thread_count];
    int index = 0;
    for(index = 0;index<max_thread_count;index++)
    {
        init_thread(&thread_array[index],thread_fun1,NULL);
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
    destroy_mutex(&mutex);
}
int main()
{
  MCHECK(foo());
  if(g_count !=1 )
  {
      DEBUG("MCHECK calls twice\n");
      abort();
  }
 
 test_multi_task_with_guard();
}
