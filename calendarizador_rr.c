#include "calendarizador_rr.h"

/*
* Algoritmo para el metodo de RR
*/
void *calendarizador_RoundRobin(void *t)
{


    Thread temporal = threads->head;
    int Quantum = 2;      //7
    int QuantumTmp = 0;
    while(1)
    {
        if(threads->head != NULL)
        {
            if(temporal != NULL)
            {
                pthread_mutex_lock(&lock_thread_actual);
                QuantumTmp = Quantum;
                thread_actual = temporal->thread_identificador;
                pthread_mutex_unlock(&lock_thread_actual);

                pthread_mutex_lock(&lock_thread_terminado);
                thread_terminado = 0;
                printf("\n");
                if(thread_actual>3)
                {
                    printf("\nComenzando a ejecutar hilo %lu", thread_actual);
                    printf(ANSI_COLOR_RED " CARRO\n" ANSI_COLOR_RESET);
                }
                else
                {
                    printf(ANSI_COLOR_RED "\nComenzando a ejecutar hilo puente %lu\n" ANSI_COLOR_RESET, thread_actual);
                }

                pthread_mutex_unlock(&lock_thread_terminado);

                while(QuantumTmp > 0 && thread_terminado == 0)
                {
                    QuantumTmp--;



                    if(hardware == 1)
                    {
                        sleep(1);

                    }
                    else
                    {
                        usleep(100000);
                    }
                }

                pthread_mutex_lock(&lock_thread_terminado);
                thread_terminado = 1;
                pthread_mutex_unlock(&lock_thread_terminado);

                usleep(10000);
                if(temporal->next != NULL)
                {
                    QuantumTmp = Quantum;
                    // printf(ANSI_COLOR_MAGENTA "Time out %lu \n" ANSI_COLOR_RESET, temporal->next->thread_identificador);
                    temporal = temporal->next;      // Obtengo el siguiente
                }
                else
                {
                    //printf("Llegue al final de la cola \n");
                    temporal = threads->head;
                }

            }
            else
            {
                temporal = threads->head;
            }

        }
        else
        {
            printf("No hay hilos para calendarizar \n");
        }
        if(hardware == 1)
        {
            sleep(1);

        }
        else if(gui == 1)
        {
            sleep(1);
        }else
        {
            usleep(100000);
        }

    }

}
