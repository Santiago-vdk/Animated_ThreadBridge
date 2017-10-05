#include "calendarizador_fcfs.h"

void *calendarizador_fcfs(void *t)
{
    // Thread thread_corriendo;
    Thread temporal = threads->head;
    while(1)
    {

        if(threads->head != NULL)
        {

            if(temporal != NULL)
            {

                pthread_mutex_lock(&lock_thread_actual);
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
                    printf( "\nComenzando a ejecutar hilo PUENTE %lu\n", thread_actual);

                }
                pthread_mutex_unlock(&lock_thread_terminado);


                while (thread_terminado == 0)
                {


                }

                if(threads->tamanio != 0 && buscar_nodo_thread(threads,thread_actual) != NULL)
                {
                    //printf(ANSI_COLOR_CYAN "Pop out & push in \n" ANSI_COLOR_RESET);
                    agregar_thread(pop_primer_thread(threads),threads);
                }

                if(temporal->next != NULL)
                {
                    temporal = temporal->next;      // Obtengo el siguiente
                }
                else
                {
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
        if(hardware == 1){
        usleep(1000000); // usleep(100000);
        } else {
        usleep(100000); // usleep(100000);
        }


    }
}
