#include <stdio.h>
#include <stdlib.h>
#include "mythreads/mythread.h"
#include "thread_data.h"
#include <time.h>
#include "puentes.h"


/*

int *controlador_carros_ley_jungla(void *carro)
{
    Thread_Carro data = (Thread_Carro) carro;

    int distancia_tmp = 0;
    while(1)
    {
        if(thread_actual == data->thread_identificador && thread_terminado == 0)
        {

            if(buscar_nodo_thread(threads,data->puente)->puente->)

            if(data->corriendo == 1)
            {
                Thread_Puente puente_tmp = buscar_nodo_thread(threads,data->puente)->puente;

                if(buscar_nodo_carro(puente_tmp->carros_circulando,data->thread_identificador)->prev == NULL )    // Si no hay carros al frente
                {
                    if(distancia_tmp == puente_tmp->capacidad)          // Ya termino de correrse todos los espacios disponibles
                    {
                        pthread_mutex_lock(&lock_thread_terminado);

                        printf(ANSI_COLOR_YELLOW "Carro %d termino de pasar el puente, no habia alguien en frente %d\n" ANSI_COLOR_RESET, data->thread_identificador, puente_tmp->carros_circulando->tamanio);

                        eliminar_nodo_thread(threads,data->thread_identificador);           // Elimino el carro de la lista de hilos
                        eliminar_nodo_carro(buscar_nodo_thread(threads,data->puente)->puente->carros_circulando,data->thread_identificador);    // Elimino el carro de la lista de los carros circulando de su debido puente
                        buscar_nodo_thread(threads,data->puente)->puente->ocupancia -= 1;

                        thread_terminado = 1;
                        distancia_tmp = 0;

                        pthread_mutex_unlock(&lock_thread_terminado);

                        pthread_t id = pthread_self();
                        pthread_detach(id);
                        return 0;
                    }
                    else
                    {
                        printf("Carro %lu moviendose %d \n", data->thread_identificador, distancia_tmp);
                        sleep(data->velocidad);                                             // Simulo la velocidad
                        distancia_tmp ++;                                                   // Auento la distancia recorrida
                    }
                }
                else                    // Hay un carro en frente
                {

                    if(distancia_tmp == puente_tmp->capacidad)          // Ya termino de correrse todos los espacios disponibles
                    {

                        pthread_mutex_lock(&lock_thread_terminado);

                        printf(ANSI_COLOR_YELLOW "Carro %d termino de pasar el puente, habia alguien en frente %d\n" ANSI_COLOR_RESET, data->thread_identificador, puente_tmp->carros_circulando->tamanio);


                        eliminar_nodo_thread(threads,data->thread_identificador);           // Elimino el carro de la lista de hilos
                        eliminar_nodo_carro(buscar_nodo_thread(threads,data->puente)->puente->carros_circulando,data->thread_identificador);    // Elimino el carro de la lista de los carros circulando de su debido puente
                        buscar_nodo_thread(threads,data->puente)->puente->ocupancia -= 1;


                        thread_terminado = 1;
                        pthread_mutex_unlock(&lock_thread_terminado);


                        pthread_t id = pthread_self();
                        pthread_detach(id);
                        return 0;

                    }
                    else
                    {
                        printf("Carro %lu moviendose %d\n", data->thread_identificador, distancia_tmp);
                        sleep(buscar_nodo_carro(puente_tmp->carros_circulando,data->thread_identificador)->prev->velocidad);                                             // Utilizo la velocidad del nodo del frente
                        distancia_tmp ++;                                        // Aumento la distancia avanzada
                    }

                }
            }
            else    // Me dieron  el procesador pero aun no me ejecuto
            {

                pthread_mutex_lock(&lock_thread_terminado);
                printf("Carro %lu no puede moverse\n", data->thread_identificador);
                thread_terminado = 1;
                pthread_mutex_unlock(&lock_thread_terminado);

            }

        }

        usleep(10000);
    }
}
*/
