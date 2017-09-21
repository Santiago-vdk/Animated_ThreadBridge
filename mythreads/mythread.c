#include <pthread.h>
#include "mythread.h"

void mythread_create(pthread_t *restrict __newthread, const pthread_attr_t *restrict __attr, void *(__start_routine)(void *), void *restrict _arg,
                     int scheduler,
                     int priority,
                     int speed,
                     int time_limit) {
    pthread_create(__newthread, __attr, __start_routine, _arg);
}
