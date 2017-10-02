#include "control_puentes_hardware.h"



void * hardware_0_lados()
{
    while(1)
    {
        if(threads != NULL)
        {
            if(threads->tamanio > 0)
            {

                if(buscar_nodo_thread(threads,0) != NULL)
                {
                    if(buscar_nodo_thread(threads,0)->puente->carros_izquierda->tamanio>0)
                    {
                        Thread_Carro primer_carro = buscar_nodo_thread(threads,0)->puente->carros_izquierda->head;
                        principal(0,primer_carro->lado_izquierdo,1,1,0,0,0,primer_carro->tipo_carro);
                        //printf(ANSI_COLOR_RED "aqusdddi tamanio %d\n" ANSI_COLOR_RESET,buscar_nodo_thread(threads,0)->puente->carros_izquierda->tamanio);
                        if(buscar_nodo_thread(threads,0)->puente->carros_izquierda->head->prev != NULL)
                        {
                            Thread_Carro segundo_carro = primer_carro->prev;
                            principal(0,segundo_carro->lado_izquierdo,1,1,0,0,0,segundo_carro->tipo_carro);
                        }
                    }

                    if(buscar_nodo_thread(threads,0)->puente->carros_derecha->tamanio>0)
                    {
                        Thread_Carro primer_carro_derecha =buscar_nodo_thread(threads,0)->puente->carros_derecha->head;
                        principal(0,primer_carro_derecha->lado_izquierdo,0,1,0,0,0,primer_carro_derecha->tipo_carro);
                        if(primer_carro_derecha->prev != NULL)
                        {
                            Thread_Carro segundo_carro_derecha = primer_carro_derecha->prev;
                            principal(0,segundo_carro_derecha->lado_izquierdo,1,1,0,0,0,segundo_carro_derecha->tipo_carro);
                        }
                    }
                }
            }

        }
        usleep(100000);
    }
}
