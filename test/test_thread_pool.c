//
// Created by liyang on 2/29/20.
//


#include <string.h>
#include <stdio.h>
#include <thread.h>
#include <thread_pool.h>
#include <count_down_latch.h>
void print()
{
    DEBUG("running\n");  
    printf("tid=%d\n", tid());
}
int main()
{
    thread_pool_class thread_pool;
    init_thread_pool(&thread_pool,"main_thread_pool");
    set_thread_pool_max_queue_size(&thread_pool,5);
    DEBUG("starting thread_pool\n");
    start_thread_pool(&thread_pool,5);

    int index = 0;
    for (;index <20;index ++)
    {
        DEBUG("pushing thread pool:%p\n",print);
        run_thread_pool(&thread_pool,print);
    }
    DEBUG("destroying\n");
     destroy_thread_pool(&thread_pool);
}
