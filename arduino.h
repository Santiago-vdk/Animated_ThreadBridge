#include "main.h"


#ifndef ARDUINO_H_INCLUDED
#define ARDUINO_H_INCLUDED
pthread_t ptSemaforo_P1,ptSemaforo_P2, ptSemaforo_P3;


void semaforo(int puente, int ladoIzquierdo, int cambio);
void *Estado_Semaforo_P1(void *arg);
void *Estado_Semaforo_P2(void *arg);
void *Estado_Semaforo_P3(void *arg);
void setup_arduino();

#endif // ARDUINO_H_INCLUDED
