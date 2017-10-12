#ifndef MYTHREAD_H_INCLUDED
#define MYTHREAD_H_INCLUDED



void mythread_create(pthread_t *restrict, const pthread_attr_t *restrict, void *(*)(void *), void *restrict);
void mythread_end(void *retval);
void mythread_yield(void);
void mythread_join(pthread_t thread, void **retval);
void mythread_detach(pthread_t thread);
//void mythread_setsched(pthread_t thread, int policy, const struct sched_param *param);

void mymutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *restrict);
void mymutex_destroy(pthread_mutex_t *mutex);
void mymutex_lock(pthread_mutex_t *mutex);
void mymutex_unlock(pthread_mutex_t *mutex);
void mymutex_trylock(pthread_mutex_t *mutex);


#endif // MYTHREAD_H_INCLUDED
