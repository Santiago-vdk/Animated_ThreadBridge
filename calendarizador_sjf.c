#include "calendarizador_sjf.h"


/*
* Algoritmo para el metodo de SJF
*/
void *calendarizador_sjf(void *t)
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
                    printf(ANSI_COLOR_RED " CARRO" ANSI_COLOR_RESET);
                    printf(" con velocidad");
                    printf(ANSI_COLOR_RED " %lf\n" ANSI_COLOR_RESET, buscar_nodo_thread(threads,thread_actual)->velocidad);

                }
                else
                {
                    printf(ANSI_COLOR_RED "\nComenzando a ejecutar hilo puente %lu con velocidad %lf\n" ANSI_COLOR_RESET, thread_actual, buscar_nodo_thread(threads,thread_actual)->velocidad);
                }
                pthread_mutex_unlock(&lock_thread_terminado);


                while (thread_terminado == 0)
                {


                }

                if(threads->tamanio != 0 && buscar_nodo_thread(threads,thread_actual) != NULL)
                {
                    //printf(ANSI_COLOR_CYAN "Pop out & push in \n" ANSI_COLOR_RESET);
                    agregar_thread_velocidad(pop_primer_thread(threads),threads);
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
