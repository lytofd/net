//
// Created by liyang on 12/4/19.
//

#ifndef RMMS_THREAD_H
#define RMMS_THREAD_H

#include <device_status.h>
#include <string.h>
#include <current_thread.h>
#include <pthread.h>
#include <stdint.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <log.h>
#define   bool int
#define  true 1
#define  false 0
typedef  void (*p_fun)();
typedef  p_fun thread_fun;
/////////////////////////////////////////////////////////////////////////
typedef struct thread_data_
{
    thread_fun  fun_;
    char  name[32];
    pid_t pid;
}thread_data_class;
void init_thread_data(thread_data_class * p_thread_data_class ,thread_fun fun,char * name,pid_t pid);
void run_in_thread(thread_data_class * p_thread_data_class);
/////////////////////////////////////////////////////////////////////////////////
void * start_thread(void * obj);

typedef struct
{
    bool started_;
    bool joined_;
    pthread_t p_thread_id_;
    p_fun  thread_fun_;
    char name_[32];
    int number_created_;
    pid_t * tid_;
}thread_class;

void init_thread(thread_class * p_thread_class, p_fun fun,char * p_name);
void  destory_thread(thread_class * p_thread_class);
void start(thread_class * p_thread_class);
int join(thread_class * p_thread_class);
#endif //RMMS_THREAD_H
