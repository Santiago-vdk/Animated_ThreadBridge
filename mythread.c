#include <pthread.h>
#include "mythread.h"

void mythread_create(pthread_t *restrict __newthread, const pthread_attr_t *restrict __attr, void *(__start_routine)(void *), void *restrict _arg)
{
    pthread_create(__newthread, __attr, __start_routine, _arg);
}
void mythread_end(void *retval)
{
    pthread_exit(retval);
}
void mythread_yield(void)
{
    pthread_yield();
}
void mythread_join(pthread_t thread, void **retval)
{
    pthread_join(thread,retval);
}
void mythread_detach(pthread_t thread)
{
    pthread_detach(thread);
}
void mymutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *_restrict){
    pthread_mutex_init(mutex,_restrict);
}
void mymutex_destroy(pthread_mutex_t *mutex){
    pthread_mutexattr_destroy(mutex);
}
void mymutex_lock(pthread_mutex_t *mutex){
    pthread_mutex_lock(mutex);
}
void mymutex_unlock(pthread_mutex_t *mutex){
    pthread_mutex_unlock(mutex);
}
void mymutex_trylock(pthread_mutex_t *mutex){
    pthread_mutex_trylock(mutex);
}
