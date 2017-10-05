#include "calendarizador_real_time.h"


/*
* Algoritmo para el metodo de Real Time
*/
void *calendarizador_real_time(void *t)
{
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
                    printf(ANSI_COLOR_RED " CARRO" ANSI_COLOR_RESET);
                    printf(" con Real Time\n");
                    // printf(ANSI_COLOR_RED " %d\n" ANSI_COLOR_RESET, buscar_nodo_thread(threads,thread_actual)->prioridad);
                }
                else
                {
                    printf(ANSI_COLOR_RED "\nComenzando a ejecutar hilo puente %lu\n" ANSI_COLOR_RESET, thread_actual);
                }
                pthread_mutex_unlock(&lock_thread_terminado);


                while (thread_terminado == 0)
                {


                }

                if(threads->tamanio != 0 && buscar_nodo_thread(threads,thread_actual) != NULL)
                {
                    //printf(ANSI_COLOR_CYAN "Pop out & push in \n" ANSI_COLOR_RESET);
                    agregar_thread_Tiempo_Real(pop_primer_thread(threads),threads);
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
        usleep(100000);

    }
}
