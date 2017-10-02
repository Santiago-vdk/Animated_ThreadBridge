#include "main.h"

#ifndef RASP_H_INCLUDED
#define RASP_H_INCLUDED

void setup_io();
void set_outputRasp();
void principal(int puente,int ladoIzquierdo,int posicion,int actPosicion,int centro,int posicionCentro,int actCentro,int tipoCarro);
void *Estado_P1(void *arg);

#endif // RASP_H_INCLUDED
