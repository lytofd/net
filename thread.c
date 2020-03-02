//
// Created by liyang on 12/4/19.
//
#include <thread.h>
#include <errno.h>
#include <unistd.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <linux/unistd.h>
__thread int t_cachedTid = 0;
__thread char t_tidString[32];
__thread int t_tidStringLength = 6;
__thread const char* t_threadName = "unknown";

/*curent id*/


/* get current thread_id*/
/// get current thread_id
/// \return
pid_t  get_tid()
{
    return (pid_t)(syscall(SYS_gettid));
}

/// cache current thread id
void cache_tid()
{
    if(t_cachedTid == 0)
    {
        t_cachedTid = get_tid();
        t_tidStringLength = snprintf(t_tidString,sizeof(t_tidString),"%5d",t_cachedTid);
    }
    return;
}

///  check if current thread is the main thread
/// \return
bool is_main_thread()
{
    return tid() == getpid();
}
/* end current thread functions*/

///////////////////////////////////////////////////////////////////////////////
//thread_data


void init_thread_data(thread_data_class * p_thread_data_class ,p_fun fun,char * name,pid_t pid)
{
    p_thread_data_class->pid = pid;
    p_thread_data_class->fun_ = fun;
    strcpy(p_thread_data_class->name,name);
}
void run_in_thread(thread_data_class * p_thread_data_class)
{
    //pid_t tid = tid();
    t_threadName =   (p_thread_data_class->name == NULL) ? "rmms_thread":p_thread_data_class->name;
    prctl(PR_SET_NAME, t_threadName);
    DEBUG("running thread function,name:%s\n",p_thread_data_class->name);
    p_thread_data_class->fun_();
    t_threadName = "finished";

}
/////////////////////////////////////////////////////////////////////////////////

void * start_thread(void * obj)
{
    thread_data_class * p_thread_data = (thread_data_class * )obj;
    run_in_thread(p_thread_data);
    if(p_thread_data)
        free(p_thread_data);
    return ;

}
//////////////////////////////////////////////////////////////////////////////
// Thread

void init_thread(thread_class * p_thread_class, p_fun fun,char * p_name)
{
    p_thread_class->started_ = false;
    p_thread_class->joined_ = false;
    p_thread_class->p_thread_id_ = 0;
    p_thread_class->tid_ = (pid_t *)malloc(sizeof(pid_t));
    p_thread_class->tid_ = 0;
    p_thread_class->thread_fun_ = fun;
    if(p_name != NULL)
    {
      strcpy(p_thread_class->name_,p_name);  
    }
    p_thread_class->number_created_ = p_thread_class->number_created_ + 1;
    if(p_thread_class->name_ == NULL)
    {
        char buf[32];
        snprintf(buf, sizeof(buf),"Thread:%d",p_thread_class->number_created_);
        memcpy(p_thread_class->name_,buf,strlen(buf));
    }
}
void  destory_thread(thread_class * p_thread_class)
{
    if(p_thread_class->started_ && !p_thread_class->joined_)
    {
        pthread_detach(p_thread_class->p_thread_id_);
    }
}
void start(thread_class * p_thread_class)
{
    assert(!p_thread_class->started_);
    p_thread_class->started_ = true;
    thread_data_class * data = malloc(sizeof(thread_data_class));
    init_thread_data(data,p_thread_class->thread_fun_,p_thread_class->name_,p_thread_class->p_thread_id_);
    if(pthread_create(&p_thread_class->p_thread_id_,NULL,start_thread,data))
    {
        p_thread_class->started_ = false;
        if(data)
            free(data);
        DEBUG("Failed in create thread\n");
	abort();
    }
}
int join(thread_class * p_thread_class)
{
    assert(p_thread_class->started_);
    assert(!p_thread_class->joined_);
    p_thread_class->joined_ = true;
    return pthread_join(p_thread_class->p_thread_id_,NULL);
}
