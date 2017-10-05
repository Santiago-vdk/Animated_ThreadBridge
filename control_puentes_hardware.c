#include "control_puentes_hardware.h"
#include "rasp.h"

void * software_0_lados()
{

//    while(1)
//    {
//
//        if(threads != NULL)
//        {
//            if(threads->tamanio > 0)
//            {
//                //printf("head %p \n", buscar_nodo_thread(threads,0)->puente->carros_izquierda->head);
//                if(buscar_nodo_thread(threads,0) != NULL)
//                {
//                    if(buscar_nodo_thread(threads,0)->puente->carros_izquierda->tamanio>0)
//                    {
//
//                        Thread_Carro primer_carro = buscar_nodo_thread(threads,0)->puente->carros_izquierda->head;
//                        primer_carro->objeto.x = 180;
//
//                        if(primer_carro->next != NULL)
//                        {
//                            Thread_Carro segundo_carro = primer_carro->next;
//                            segundo_carro->objeto.x = 125;
//
//                            if(segundo_carro->next != NULL)
//                            {
//                                Thread_Carro tercer_carro = segundo_carro->next;
//                                tercer_carro->objeto.x = 70;
//                            }
//                        }
//
//
//                    }
//
//                  /*  if(buscar_nodo_thread(threads,0)->puente->carros_derecha->tamanio>0)
//                    {
//                        Thread_Carro primer_carro_derecha =buscar_nodo_thread(threads,0)->puente->carros_derecha->head;
//                        primer_carro_derecha->objeto.x = SCREEN_WIDTH - 225;
//
//                        if(primer_carro_derecha->next != NULL)
//                        {
//                            Thread_Carro segundo_carro_derecha = primer_carro_derecha->next;
//                            segundo_carro_derecha->objeto.x =  SCREEN_WIDTH - 190;
//                        }
//
//
//                    }*/
//                }
//                /*    else if(buscar_nodo_puente(puentes,0) != NULL)
//                    {
//                        if(buscar_nodo_puente(puentes,0)->carros_izquierda->tamanio>0)
//                        {
//                            Thread_Carro primer_carro = buscar_nodo_puente(puentes,0)->carros_izquierda->head;
//
//
//
//                            if(primer_carro->next != NULL)
//                            {
//                                Thread_Carro segundo_carro = primer_carro->next;
//
//                            }
//
//                        }
//
//
//                        if(buscar_nodo_puente(puentes,0)->carros_derecha->tamanio>0)
//                        {
//                            Thread_Carro primer_carro_derecha = buscar_nodo_puente(puentes,0)->carros_derecha->head;
//
//
//                            if(primer_carro_derecha->next != NULL)
//                            {
//                                Thread_Carro segundo_carro_derecha = primer_carro_derecha->next;
//
//                            }
//                        }
//
//
//                    }*/
//
//            }
//
//        }
//        usleep(10000);
//    }

}

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


                        if(primer_carro->next != NULL)
                        {
                            Thread_Carro segundo_carro = primer_carro->next;
                            principal(0,segundo_carro->lado_izquierdo,0,1,0,0,0,segundo_carro->tipo_carro);
                        }

                    }
                    else
                    {
                        Apagar_P1_Izq();
                    }

                    if(buscar_nodo_thread(threads,0)->puente->carros_derecha->tamanio>0)
                    {
                        Thread_Carro primer_carro_derecha =buscar_nodo_thread(threads,0)->puente->carros_derecha->head;
                        principal(0,primer_carro_derecha->lado_izquierdo,0,1,0,0,0,primer_carro_derecha->tipo_carro);

                        if(primer_carro_derecha->next != NULL)
                        {
                            Thread_Carro segundo_carro_derecha = primer_carro_derecha->next;
                            principal(0,segundo_carro_derecha->lado_izquierdo,1,1,0,0,0,segundo_carro_derecha->tipo_carro);
                        }
                    }
                    else
                    {

                        Apagar_P1_Der();
                    }
                }
                else if(buscar_nodo_puente(puentes,0) != NULL)
                {
                    if(buscar_nodo_puente(puentes,0)->carros_izquierda->tamanio>0)
                    {
                        Thread_Carro primer_carro = buscar_nodo_puente(puentes,0)->carros_izquierda->head;
                        principal(0,primer_carro->lado_izquierdo,1,1,0,0,0,primer_carro->tipo_carro);


                        if(primer_carro->next != NULL)
                        {
                            Thread_Carro segundo_carro = primer_carro->next;
                            principal(0,segundo_carro->lado_izquierdo,0,1,0,0,0,segundo_carro->tipo_carro);
                        }

                    }
                    else
                    {
                        Apagar_P1_Izq();
                    }

                    if(buscar_nodo_puente(puentes,0)->carros_derecha->tamanio>0)
                    {
                        Thread_Carro primer_carro_derecha = buscar_nodo_puente(puentes,0)->carros_derecha->head;
                        principal(0,primer_carro_derecha->lado_izquierdo,0,1,0,0,0,primer_carro_derecha->tipo_carro);

                        if(primer_carro_derecha->next != NULL)
                        {
                            Thread_Carro segundo_carro_derecha = primer_carro_derecha->next;
                            principal(0,segundo_carro_derecha->lado_izquierdo,1,1,0,0,0,segundo_carro_derecha->tipo_carro);
                        }
                    }
                    else
                    {

                        Apagar_P1_Der();
                    }

                }
                else
                {
                    printf(ANSI_COLOR_RED "Error representando HW del puente 0\n" ANSI_COLOR_RESET);
                }
            }
            else
            {
                Apagar_P1_Izq();
                Apagar_P1_Der();

            }

        }
        sleep(1);
    }
}


void * hardware_1_lados()
{
    while(1)
    {
        if(threads != NULL)
        {
            if(threads->tamanio > 0)
            {

                if(buscar_nodo_thread(threads,1) != NULL)
                {
                    if(buscar_nodo_thread(threads,1)->puente->carros_izquierda->tamanio>0)
                    {
                        Thread_Carro primer_carro = buscar_nodo_thread(threads,1)->puente->carros_izquierda->head;
                        principal(1,primer_carro->lado_izquierdo,1,1,0,0,0,primer_carro->tipo_carro);

                        if(primer_carro->next != NULL)
                        {
                            Thread_Carro segundo_carro = primer_carro->next;
                            principal(1,segundo_carro->lado_izquierdo,0,1,0,0,0,segundo_carro->tipo_carro);
                        }

                    }
                    else
                    {
                        Apagar_P2_Izq();
                    }

                    if(buscar_nodo_thread(threads,1)->puente->carros_derecha->tamanio>0)
                    {
                        Thread_Carro primer_carro_derecha =buscar_nodo_thread(threads,1)->puente->carros_derecha->head;
                        principal(1,primer_carro_derecha->lado_izquierdo,0,1,0,0,0,primer_carro_derecha->tipo_carro);

                        if(primer_carro_derecha->next != NULL)
                        {
                            Thread_Carro segundo_carro_derecha = primer_carro_derecha->next;
                            principal(1,segundo_carro_derecha->lado_izquierdo,1,1,0,0,0,segundo_carro_derecha->tipo_carro);
                        }
                    }
                    else
                    {

                        Apagar_P2_Der();
                    }
                }
                else if(buscar_nodo_puente(puentes,1) != NULL)
                {

                    if(buscar_nodo_puente(puentes,1)->carros_izquierda->tamanio>0)
                    {
                        Thread_Carro primer_carro = buscar_nodo_puente(puentes,1)->carros_izquierda->head;
                        principal(1,primer_carro->lado_izquierdo,1,1,0,0,0,primer_carro->tipo_carro);


                        if(primer_carro->next != NULL)
                        {
                            Thread_Carro segundo_carro = primer_carro->next;
                            principal(1,segundo_carro->lado_izquierdo,0,1,0,0,0,segundo_carro->tipo_carro);
                        }

                    }
                    else
                    {
                        Apagar_P1_Izq();
                    }

                    if(buscar_nodo_puente(puentes,1)->carros_derecha->tamanio>0)
                    {
                        Thread_Carro primer_carro_derecha = buscar_nodo_puente(puentes,1)->carros_derecha->head;
                        principal(1,primer_carro_derecha->lado_izquierdo,0,1,0,0,0,primer_carro_derecha->tipo_carro);

                        if(primer_carro_derecha->next != NULL)
                        {
                            Thread_Carro segundo_carro_derecha = primer_carro_derecha->next;
                            principal(1,segundo_carro_derecha->lado_izquierdo,1,1,0,0,0,segundo_carro_derecha->tipo_carro);
                        }
                    }
                    else
                    {

                        Apagar_P1_Der();
                    }
                }
                else
                {
                    printf(ANSI_COLOR_RED "Error representando HW del puente 1\n" ANSI_COLOR_RESET);
                }
            }
            else
            {
                Apagar_P2_Izq();
                Apagar_P2_Der();

            }

        }
        sleep(1);
    }
}


void * hardware_2_lados()
{
    while(1)
    {
        if(threads != NULL)
        {
            if(threads->tamanio > 0)
            {

                if(buscar_nodo_thread(threads,2) != NULL)
                {
                    if(buscar_nodo_thread(threads,2)->puente->carros_izquierda->tamanio>0)
                    {
                        Thread_Carro primer_carro = buscar_nodo_thread(threads,2)->puente->carros_izquierda->head;
                        principal(2,primer_carro->lado_izquierdo,1,1,0,0,0,primer_carro->tipo_carro);

                        if(primer_carro->next != NULL)
                        {
                            Thread_Carro segundo_carro = primer_carro->next;
                            principal(2,segundo_carro->lado_izquierdo,0,1,0,0,0,segundo_carro->tipo_carro);
                        }
                    }
                    else
                    {

                        Apagar_P3_Izq();
                    }
                    if(buscar_nodo_thread(threads,2)->puente->carros_derecha->tamanio>0)
                    {
                        Thread_Carro primer_carro_derecha =buscar_nodo_thread(threads,2)->puente->carros_derecha->head;
                        principal(2,primer_carro_derecha->lado_izquierdo,0,1,0,0,0,primer_carro_derecha->tipo_carro);

                        if(primer_carro_derecha->next != NULL)
                        {
                            Thread_Carro segundo_carro_derecha = primer_carro_derecha->next;
                            principal(2,segundo_carro_derecha->lado_izquierdo,1,1,0,0,0,segundo_carro_derecha->tipo_carro);
                        }

                    }
                    else
                    {
                        Apagar_P3_Der();
                    }
                }
                else if(buscar_nodo_puente(puentes,2) != NULL)
                {

                    if(buscar_nodo_puente(puentes,2)->carros_izquierda->tamanio>0)
                    {
                        Thread_Carro primer_carro = buscar_nodo_puente(puentes,2)->carros_izquierda->head;
                        principal(2,primer_carro->lado_izquierdo,1,1,0,0,0,primer_carro->tipo_carro);


                        if(primer_carro->next != NULL)
                        {
                            Thread_Carro segundo_carro = primer_carro->next;
                            principal(2,segundo_carro->lado_izquierdo,0,1,0,0,0,segundo_carro->tipo_carro);
                        }

                    }
                    else
                    {
                        Apagar_P1_Izq();
                    }

                    if(buscar_nodo_puente(puentes,2)->carros_derecha->tamanio>0)
                    {
                        Thread_Carro primer_carro_derecha = buscar_nodo_puente(puentes,2)->carros_derecha->head;
                        principal(2,primer_carro_derecha->lado_izquierdo,0,1,0,0,0,primer_carro_derecha->tipo_carro);

                        if(primer_carro_derecha->next != NULL)
                        {
                            Thread_Carro segundo_carro_derecha = primer_carro_derecha->next;
                            principal(2,segundo_carro_derecha->lado_izquierdo,1,1,0,0,0,segundo_carro_derecha->tipo_carro);
                        }
                    }
                    else
                    {

                        Apagar_P1_Der();
                    }
                }
                else
                {
                    printf(ANSI_COLOR_RED "Error representando HW del puente 2\n" ANSI_COLOR_RESET);
                }
            }
            else
            {
                Apagar_P3_Izq();
                Apagar_P3_Der();

            }

        }
        sleep(1);
    }
}
