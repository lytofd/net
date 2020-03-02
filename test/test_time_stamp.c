//
// Created by liyang on 2/28/20.
//

#include <time_stamp.h>
#include <stdio.h>

int main()
{
    time_t t;
    t = time(NULL);
    int ii = time(&t);
    printf("ii = %d\n", ii);
    ///
    time_stamp_class  * p_front = now();
    char buf[32]={0};
    time_stamp_to_string(p_front,buf,32);
    DEBUG("now time:%s\n",buf);
    sleep(10);
    char bufs[32] = {0};
    time_stamp_class  * p_back = now();
    time_stamp_to_string(p_back,bufs,32);
    DEBUG("now time:%s\n",bufs);
    int time_dif = time_difference(p_back,p_front);
    DEBUG("time difference:%ld\n",time_dif);
}
