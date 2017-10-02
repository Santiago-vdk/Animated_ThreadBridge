#ifndef MYTHREAD_H_INCLUDED
#define MYTHREAD_H_INCLUDED

/*

void mythread_create(pthread_t *restrict, const pthread_attr_t *restrict, void *(*)(void *), void *restrict,
                     int scheduler,
                     int priority,
                     int speed,
                     int time_limit);
void mythread_end(void *);
void mythread_yield(void);
void mythread_join(pthread_t, void **);
void mythread_detach(pthread_t);
void mythread_setsched(int scheduler);

void mymutex_init(pthread_mutex_t *restrict, const pthread_mutexattr_t *restrict);
void mymutex_destroy(pthread_mutex_t *);
void mymutex_lock(pthread_mutex_t *);
void mymutex_unlock(pthread_mutex_t *);
void mymutex_trylock(pthread_mutex_t *);

*/
#endif // MYTHREAD_H_INCLUDED
