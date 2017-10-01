#include <stdio.h>
#include <stdlib.h>
#include "mythreads/mythread.h"
#include "thread_data.h"
#include <time.h>
#include "puentes.h"
#include <unistd.h>
#include <math.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

long thread_actual = -1;
int thread_terminado = 1;
int calendarizador = -1;

pthread_t thread_calendarizador;
pthread_t thread_generador_carros;

pthread_mutex_t lock_thread_terminado;
pthread_mutex_t lock_thread_actual;
pthread_mutex_t lock_contador_tmp;
pthread_mutex_t lock_carro_movimiento;
pthread_mutex_t lock_modificar_lista;

pthread_mutex_t lock_comenzar_espera;
pthread_mutex_t lock_agregarse;

ThreadList threads;
ThreadListPuente puentes;


void *calendarizador_RoundRobin(void *t)
{


    Thread temporal = threads->head;
    int Quantum = 7;      //200
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
                    printf("\nComenzando a ejecutar hilo %d", thread_actual);
                    printf(ANSI_COLOR_RED " CARRO\n" ANSI_COLOR_RESET);
                }
                else
                {
                    printf(ANSI_COLOR_RED "\nComenzando a ejecutar hilo puente %d\n" ANSI_COLOR_RESET, thread_actual);
                }

                pthread_mutex_unlock(&lock_thread_terminado);

                while(QuantumTmp > 0)
                {
                    QuantumTmp--;
                    usleep(100000);
                }

                pthread_mutex_lock(&lock_thread_terminado);
                thread_terminado = 1;
                pthread_mutex_unlock(&lock_thread_terminado);

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

        usleep(100000);
    }

}


void *calendarizador_priority_queue(void *t)
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
                    printf("\nComenzando a ejecutar hilo %d", thread_actual);
                    printf(ANSI_COLOR_RED " CARRO\n" ANSI_COLOR_RESET);
                }
                else
                {
                    printf(ANSI_COLOR_RED "\nComenzando a ejecutar hilo puente %d\n" ANSI_COLOR_RESET, thread_actual);
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
        usleep(100000);

    }
}
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
                    printf("\nComenzando a ejecutar hilo %d", thread_actual);
                    printf(ANSI_COLOR_RED " CARRO\n" ANSI_COLOR_RESET);

                }
                else
                {
                    printf( "\nComenzando a ejecutar hilo PUENTE %d\n", thread_actual);

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
        usleep(100000);

    }
}



int *controlador_carros(void *carro)
{
    Thread_Carro data = (Thread_Carro) carro;

    int distancia_tmp = 0;
    while(1)
    {

        if(thread_actual == data->thread_identificador && thread_terminado == 0)
        {

            if(data->corriendo == 1)
            {
                Thread_Puente puente_tmp = buscar_nodo_thread(threads,data->puente)->puente;

                if(buscar_nodo_carro(puente_tmp->carros_circulando,data->thread_identificador)->prev == NULL )    // Si no hay carros al frente
                {
                    if(distancia_tmp == puente_tmp->capacidad)          // Ya termino de correrse todos los espacios disponibles
                    {

                        pthread_mutex_lock(&lock_thread_terminado);

                        printf(ANSI_COLOR_BLUE "Carro %d termino de pasar el puente, no habia alguien en frente %d\n" ANSI_COLOR_RESET, data->thread_identificador, puente_tmp->carros_circulando->tamanio);

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
                        //printf("Carro %lu moviendose %d \n", data->thread_identificador, distancia_tmp);
                        sleep(data->velocidad);                                             // Simulo la velocidad
                        distancia_tmp ++;                                                   // Auento la distancia recorrida
                    }
                }
                else                    // Hay un carro en frente
                {

                    if(distancia_tmp == puente_tmp->capacidad)          // Ya termino de correrse todos los espacios disponibles
                    {

                        pthread_mutex_lock(&lock_thread_terminado);

                        printf(ANSI_COLOR_BLUE "Carro %d termino de pasar el puente, habia alguien en frente %d\n" ANSI_COLOR_RESET, data->thread_identificador, puente_tmp->carros_circulando->tamanio);


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
                        //printf("Carro %lu moviendose %d\n", data->thread_identificador, distancia_tmp);
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


void *algoritmo_puente_oficial(void *puente)
{

    Thread_Puente data = (Thread_Puente) puente;
    int temporal_k_izquierda = 0;
    int temporal_k_derecha = 0;
    while(1)
    {

        if(thread_actual == data->thread_identificador && thread_terminado == 0)
        {

            while(temporal_k_izquierda <= data->k) // Proceso lado izquierdo
            {
                if(temporal_k_izquierda == data->k)
                {

                    pthread_mutex_lock(&lock_thread_terminado);
                    printf(ANSI_COLOR_RED "Trafico termino" ANSI_COLOR_RESET);
                    printf(" de dejar pasar sus carros del lado izquierdo\n");
                    //temporal_k_izquierda = 0;
                    thread_terminado = 1;
                    pthread_mutex_unlock(&lock_thread_terminado);
                    break;

                }

                if (data->ocupancia == data->capacidad)         // Puente lleno
                {
                    printf(ANSI_COLOR_RED "Puente lleno," ANSI_COLOR_RESET);
                    printf(" haciendo esperar a los carros de la izquierda  \n");
                    pthread_mutex_lock(&lock_thread_terminado);
                    thread_terminado = 1;
                    pthread_mutex_unlock(&lock_thread_terminado);

                    break;
                }
                else                                            // Puente con campo
                {
                    if((data->carros_izquierda->tamanio > 0) && (data->ocupancia < data->capacidad))
                    {

                        Thread_Carro tmp = pop_primer_thread_carro(data->carros_izquierda); // Extraigo la cabeza de la lista del lado izquierdo y reordeno
                        agregar_carro(tmp,data->carros_circulando);     // Paso el thread a los que estan circulando

                        pthread_mutex_lock(&lock_contador_tmp);
                        buscar_nodo_thread(threads,tmp->thread_identificador)->carro->corriendo = 1; // Poner a caminar el carro

                        if(tmp->tipo_carro == RADIOACTIVO)
                        {
                            printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                        }
                        else if(tmp->tipo_carro == AMBULANCIA)
                        {
                            printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                        }
                        else
                        {
                            printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                        }

                        data->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad
                        temporal_k_izquierda += 1;
                        pthread_mutex_unlock(&lock_contador_tmp);

                    }
                    else
                    {
                        pthread_mutex_lock(&lock_thread_terminado);
                        printf(ANSI_COLOR_RED "No hay carros" ANSI_COLOR_RESET);
                        printf(" a la izquierda del puente \n");
                        thread_terminado = 1;
                        temporal_k_izquierda = data->k;
                        pthread_mutex_unlock(&lock_thread_terminado);

                        break;
                    }
                }
            }



            if(temporal_k_izquierda == data->k)             // Si ya se proceso el lado izquierdo
            {

                while(temporal_k_derecha <= data->k) // Proceso lado izquierdo
                {
                    if(temporal_k_derecha == data->k)
                    {

                        pthread_mutex_lock(&lock_thread_terminado);
                        printf(ANSI_COLOR_RED "Trafico termino" ANSI_COLOR_RESET);
                        printf(" de dejar pasar sus carros del lado derecho\n");
                        temporal_k_derecha = 0;             // Reinicio temporal
                        temporal_k_izquierda = 0;           // Reinicio temporal
                        thread_terminado = 1;
                        pthread_mutex_unlock(&lock_thread_terminado);
                        break;

                    }

                    if (data->ocupancia == data->capacidad)         // Puente lleno
                    {
                        printf(ANSI_COLOR_RED "Puente lleno," ANSI_COLOR_RESET);
                        printf(" haciendo esperar a los carros de la derecha  \n");
                        pthread_mutex_lock(&lock_thread_terminado);
                        thread_terminado = 1;
                        pthread_mutex_unlock(&lock_thread_terminado);

                        break;
                    }
                    else                                            // Puente con campo
                    {
                        if((data->carros_derecha->tamanio > 0) && (data->ocupancia < data->capacidad))
                        {

                            Thread_Carro tmp = pop_primer_thread_carro(data->carros_derecha); // Extraigo la cabeza de la lista del lado izquierdo y reordeno
                            agregar_carro(tmp,data->carros_circulando);     // Paso el thread a los que estan circulando

                            pthread_mutex_lock(&lock_contador_tmp);
                            buscar_nodo_thread(threads,tmp->thread_identificador)->carro->corriendo = 1; // Poner a caminar el carro


                            if(tmp->tipo_carro == RADIOACTIVO)
                            {
                                printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                            }
                            else if(tmp->tipo_carro == AMBULANCIA)
                            {
                                printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                            }
                            else
                            {
                                printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                            }


                            data->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad
                            temporal_k_derecha += 1;
                            pthread_mutex_unlock(&lock_contador_tmp);

                        }
                        else
                        {
                            pthread_mutex_lock(&lock_thread_terminado);
                            printf(ANSI_COLOR_RED "No hay carros" ANSI_COLOR_RESET);
                            printf(" a la derecha del puente \n");
                            thread_terminado = 1;
                            temporal_k_derecha = data->k;
                            temporal_k_izquierda = 0;

                            pthread_mutex_unlock(&lock_thread_terminado);

                            break;
                        }
                    }
                }
            }
        }
    }
}

void *algoritmo_puente_semaforo(void *puente)
{
    Thread_Puente data = (Thread_Puente) puente;
    int espera_tmp =0;

    while(1)
    {
        if(thread_actual == data->thread_identificador && thread_terminado == 0)
        {

            if(data->carros_circulando->head != NULL)
            {
                if(((data->carros_circulando->head->lado_izquierdo == 0) && (data->semaforo_izquierda == 1)) ||
                        ((data->carros_circulando->head->lado_izquierdo == 1) && (data->semaforo_izquierda == 0)))
                {
                    printf(ANSI_COLOR_YELLOW "Espera Amarillo en PUENTE %lu\n" ANSI_COLOR_RESET, data->thread_identificador);
                    pthread_mutex_lock(&lock_thread_terminado);
                    thread_terminado = 1;
                    pthread_mutex_unlock(&lock_thread_terminado);
                    break;
                }
            }


            if(data->semaforo_izquierda == 1)        // el izquierdo esta encendido en verde
            {
                data->temporizando = 1;     // Se auto indica que esta esperando
                espera_tmp = data->temporizado_parcial;

                while(espera_tmp <= data->tiempo_semaforo_izquierda && thread_actual == data->thread_identificador && thread_terminado == 0)          // Mientras no se dispare el temporizador
                {
                    if(thread_actual == data->thread_identificador && thread_terminado == 0)
                    {
                        if(espera_tmp == data->tiempo_semaforo_izquierda)
                        {
                            data->temporizando = 0;
                            break;
                        }
                        while(data->carros_izquierda->tamanio > 0 && data->carros_circulando->tamanio < data->capacidad)
                        {
                            if(thread_actual == data->thread_identificador && thread_terminado == 0)
                            {
                                Thread_Carro tmp = pop_primer_thread_carro(data->carros_izquierda); // Extraigo la cabeza de la lista del lado izquierdo y reordeno
                                agregar_carro(tmp,data->carros_circulando);     // Paso el thread a los que estan circulando
                                if(tmp->tipo_carro == RADIOACTIVO)
                                {
                                    printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                                }
                                else if(tmp->tipo_carro == AMBULANCIA)
                                {
                                    printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                                }
                                else
                                {
                                    printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                                };

                                buscar_nodo_thread(threads,tmp->thread_identificador)->carro->corriendo = 1; // Poner a caminar el carro
                                data->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad
                            }
                            else
                            {
                                data->temporizado_parcial = espera_tmp;
                                pthread_mutex_lock(&lock_thread_terminado);
                                thread_terminado = 1;
                                pthread_mutex_unlock(&lock_thread_terminado);
                                break;
                            }

                        }
                        espera_tmp += 1;

                    }
                    else
                    {
                        data->temporizado_parcial = espera_tmp;
                        pthread_mutex_lock(&lock_thread_terminado);
                        thread_terminado = 1;
                        break;
                        pthread_mutex_unlock(&lock_thread_terminado);
                    }

                }

                espera_tmp = 0;
                //printf("Sali \n");
                printf("Cambio semaforo izquierda a");
                printf(ANSI_COLOR_RED " rojo" ANSI_COLOR_RESET);
                printf(" y derecho a");
                printf(ANSI_COLOR_GREEN " verde" ANSI_COLOR_RESET);
                printf(" en PUENTE %d \n", data->puente_id);

                data->semaforo_izquierda = 0; //izquierda a rojo
                //pthread_mutex_unlock(&lock_comenzar_espera);
            }

            if(data->semaforo_izquierda == 0)
            {

                //pthread_mutex_lock(&lock_comenzar_espera);
                data->temporizando = 1;     // Se auto indica que esta esperando
                espera_tmp = data->temporizado_parcial;

                while(espera_tmp <= data->tiempo_semaforo_derecha && thread_actual == data->thread_identificador && thread_terminado == 0)          // Mientras no se dispare el temporizador
                {
                    if(thread_actual == data->thread_identificador && thread_terminado == 0)
                    {
                        if(espera_tmp == data->tiempo_semaforo_derecha)
                        {
                            data->temporizando = 0;
                            break;
                        }
                        while(data->carros_derecha->tamanio > 0 && data->carros_circulando->tamanio < data->capacidad)
                        {
                            if(thread_actual == data->thread_identificador && thread_terminado == 0)
                            {
                                Thread_Carro tmp = pop_primer_thread_carro(data->carros_derecha); // Extraigo la cabeza de la lista del lado izquierdo y reordeno
                                agregar_carro(tmp,data->carros_circulando);     // Paso el thread a los que estan circulando

                                if(tmp->tipo_carro == RADIOACTIVO)
                                {
                                    printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                                }
                                else if(tmp->tipo_carro == AMBULANCIA)
                                {
                                    printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                                }
                                else
                                {
                                    printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                                }

                                buscar_nodo_thread(threads,tmp->thread_identificador)->carro->corriendo = 1; // Poner a caminar el carro
                                data->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad

                            }
                            else
                            {
                                data->temporizado_parcial = espera_tmp;
                                pthread_mutex_lock(&lock_thread_terminado);
                                thread_terminado = 1;
                                pthread_mutex_unlock(&lock_thread_terminado);
                                break;


                            }

                        }

                        //usleep(1000000);
                        espera_tmp += 1;

                    }
                    else
                    {
                        data->temporizado_parcial = espera_tmp;
                        pthread_mutex_lock(&lock_thread_terminado);
                        thread_terminado = 1;
                        pthread_mutex_unlock(&lock_thread_terminado);
                        break;

                    }

                }

                espera_tmp = 0;
                //printf("Sali \n");

                printf("Cambio semaforo derecha a");
                printf(ANSI_COLOR_RED " rojo" ANSI_COLOR_RESET);
                printf(" y izquierdo a");
                printf(ANSI_COLOR_GREEN " verde" ANSI_COLOR_RESET);
                printf(" en PUENTE %d \n", data->puente_id);


                data->semaforo_izquierda = 1; //izquierda a rojo
                //pthread_mutex_unlock(&lock_comenzar_espera);

                pthread_mutex_lock(&lock_thread_terminado);
                thread_terminado = 1;
                pthread_mutex_unlock(&lock_thread_terminado);


            }


        }
        usleep(1000000);
    }
}


void *controlador_carros_jungla(void *carro)
{
    Thread_Carro data = (Thread_Carro) carro;

    int distancia_tmp = 0;
    long id = data->thread_identificador;
    int corriendo = data->corriendo;
    int puente = data->puente;
    while(1)
    {
        if(thread_actual == id && thread_terminado == 0)
        {
            if(corriendo == 0)
            {
                Thread_Puente puente_temporal = buscar_nodo_puente(puentes,puente);
                if(puente_temporal->carros_circulando->tamanio < puente_temporal->capacidad)  // Hay espacio para pasar
                {
                    if(data->lado_izquierdo == 1)           // Estoy en el lado izquierdo del puente
                    {
                        if(puente_temporal->carros_circulando->head == NULL)
                        {
                            eliminar_nodo_carro(puente_temporal->carros_izquierda, id);
                            agregar_carro(data,puente_temporal->carros_circulando);     // Paso el thread a los que estan circulando


                            if(data->tipo_carro == RADIOACTIVO)
                            {
                                printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else if(data->tipo_carro == AMBULANCIA)
                            {
                                printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else
                            {
                                printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, id, puente);
                            }


                            corriendo = 1; // Poner a caminar el carro
                            puente_temporal->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad
                        }
                        else if(puente_temporal->carros_circulando->head->lado_izquierdo == 1 && puente_temporal->carros_circulando < puente_temporal->capacidad)
                        {

                            agregar_carro(data,puente_temporal->carros_circulando);     // Paso el thread a los que estan circulando
                            eliminar_nodo_carro(puente_temporal->carros_izquierda, id);

                            if(data->tipo_carro == RADIOACTIVO)
                            {
                                printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else if(data->tipo_carro == AMBULANCIA)
                            {
                                printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else
                            {
                                printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, id, puente);
                            }

                            corriendo = 1; // Poner a caminar el carro
                            puente_temporal->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es s
                        }
                        else
                        {
                            // printf("No pude entrar, viene gente del otro lado\n");
                        }

                    }
                    else
                    {
                        if(puente_temporal->carros_circulando->head == NULL)
                        {
                            eliminar_nodo_carro(puente_temporal->carros_derecha, id);
                            agregar_carro(data,puente_temporal->carros_circulando);     // Paso el thread a los que estan circulando


                            if(data->tipo_carro == RADIOACTIVO)
                            {
                                printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else if(data->tipo_carro == AMBULANCIA)
                            {
                                printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else
                            {
                                printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, id, puente);
                            }

                            corriendo = 1; // Poner a caminar el carro
                            puente_temporal->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad

                        }
                        else if(puente_temporal->carros_circulando->head->lado_izquierdo == 1 && puente_temporal->carros_circulando < puente_temporal->capacidad)
                        {
                            agregar_carro(data,puente_temporal->carros_circulando);     // Paso el thread a los que estan circulando
                            eliminar_nodo_carro(puente_temporal->carros_derecha, id);

                            if(data->tipo_carro == RADIOACTIVO)
                            {
                                printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else if(data->tipo_carro == AMBULANCIA)
                            {
                                printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else
                            {
                                printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, id, puente);
                            }


                            corriendo = 1; // Poner a caminar el carro
                            puente_temporal->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es s
                        }
                        else
                        {
                            //printf("No pude entrar, viene gente del otro lado\n");
                        }
                    }
                }

            }

            else if(corriendo == 1)
            {
                Thread_Puente puente_tmp = buscar_nodo_puente(puentes,data->puente);

                if(buscar_nodo_carro(puente_tmp->carros_circulando,id) != NULL )    // Si no hay carros al frente
                {
                    if(buscar_nodo_carro(puente_tmp->carros_circulando,id)->prev == NULL )
                    {

                        if(distancia_tmp == puente_tmp->capacidad)          // Ya termino de correrse todos los espacios disponibles
                        {
                            pthread_mutex_lock(&lock_thread_terminado);
                            eliminar_nodo_carro(buscar_nodo_puente(puentes,data->puente)->carros_circulando,id);    // Elimino el carro de la lista de los carros circulando de su debido puente
                            eliminar_nodo_thread(threads,id);           // Elimino el carro de la lista de hilos
                            buscar_nodo_puente(puentes,data->puente)->ocupancia -= 1;
                            distancia_tmp = 0;
                            printf(ANSI_COLOR_YELLOW "Carro %d termino de pasar el puente, no habia alguien en frente %d\n" ANSI_COLOR_RESET, id, puente_tmp->carros_circulando->tamanio);
                            thread_terminado = 1;
                            pthread_mutex_unlock(&lock_thread_terminado);
                            pthread_t id = pthread_self();
                            pthread_detach(id);
                            break;
                            // return 0;
                        }
                        else
                        {
                            printf("Carro %lu moviendose %d \n", id, distancia_tmp);
                            usleep(data->velocidad*100000);                                             // Simulo la velocidad
                            distancia_tmp ++;                                                   // Auento la distancia recorrida
                        }
                    }
                    else                      // Hay un carro en frente
                    {

                        if(distancia_tmp == puente_tmp->capacidad)          // Ya termino de correrse todos los espacios disponibles
                        {

                            pthread_mutex_lock(&lock_thread_terminado);
                            eliminar_nodo_carro( buscar_nodo_puente(puentes,data->puente)->carros_circulando,id);    // Elimino el carro de la lista de los carros circulando de su debido puente
                            eliminar_nodo_thread(threads,id);           // Elimino el carro de la lista de hilos
                            buscar_nodo_puente(puentes,data->puente)->ocupancia -= 1;
                            printf(ANSI_COLOR_YELLOW "Carro %d termino de pasar el puente, habia alguien en frente %d\n" ANSI_COLOR_RESET, id, puente_tmp->carros_circulando->tamanio);
                            thread_terminado = 1;
                            pthread_mutex_unlock(&lock_thread_terminado);
                            pthread_t id = pthread_self();
                            pthread_detach(id);
                            break;
                            // return 0;

                        }
                        else
                        {
                            printf("Carro %lu moviendose %d\n", id, distancia_tmp);
                            usleep(buscar_nodo_carro(puente_tmp->carros_circulando,id)->prev->velocidad*100000);                                             // Utilizo la velocidad del nodo del frente
                            distancia_tmp ++;                                        // Aumento la distancia avanzada
                        }

                    }

                }



            }
            else
            {

                printf("Undefined\n");
            }

            usleep(100000);

        }
    }


}


// Utiliza la lista global de los hilos para encontrar el puente en el que tiene que insertar carros
void *generador_carros(void *t)
{
    int i = 4;
    //pthread_t array [10000];
    double lambda = 0.5;
    double probabilidad = 0;
    double porcentaje_ambulancia = 0;
    while(i)
    {
        srand(time(NULL));
        //printf("Generando carro %lu de tipo %d al lado %d del puente %d \n",i, carro->tipo_carro, lado_random, puente_random);

        int puente_random = rand() % 4;
        int lado_random =0; //rand() % 2;

        Thread_Carro carro = (Thread_Carro) calloc(1, sizeof(struct thread_carro));
        carro -> thread_identificador = i;
        carro -> corriendo = 0;
        carro -> puente = puente_random;
        carro -> velocidad = rand() / (RAND_MAX + 1.);


        switch (puente_random)
        {
        case 0:
            probabilidad = lambda*pow(2.71828,-lambda*getParameterValueConfigDouble("config_puente_0.txt","distribucion_exponencial"));
            porcentaje_ambulancia = getParameterValueConfigDouble("config_puente_0.txt","probabilidad_ambulancia");
            break;
        case 1:
            probabilidad = lambda*pow(2.71828,-lambda*getParameterValueConfigDouble("config_puente_1.txt","distribucion_exponencial"));
            porcentaje_ambulancia = getParameterValueConfigDouble("config_puente_1.txt","probabilidad_ambulancia");
            break;
        case 2:
            probabilidad = lambda*pow(2.71828,-lambda*getParameterValueConfigDouble("config_puente_2.txt","distribucion_exponencial"));
            porcentaje_ambulancia = getParameterValueConfigDouble("config_puente_2.txt","probabilidad_ambulancia");
            break;
        case 3:
            probabilidad = lambda*pow(2.71828,-lambda*getParameterValueConfigDouble("config_puente_3.txt","distribucion_exponencial"));
            porcentaje_ambulancia = getParameterValueConfigDouble("config_puente_3.txt","probabilidad_ambulancia");
            break;
        }


        if(rand() < probabilidad *( (double) RAND_MAX) )
        {
            carro -> tipo_carro = RADIOACTIVO;
            carro -> prioridad = 0;
            carro -> vida_carro = 10;
        }

        else
        {
            if(rand()%100 < porcentaje_ambulancia*100)
            {
                carro -> tipo_carro = AMBULANCIA;
                carro -> prioridad = 1;
                carro -> vida_carro = 40;
            }
            else
            {
                carro -> tipo_carro = CARRO;
                carro -> prioridad = 2;
                carro -> vida_carro = -1;
            }
        }


        carro -> limite_tiempo = -1;



        pthread_t carro_thread;
        if(lado_random == 0)        // Izquierda
        {
            carro->lado_izquierdo = 1;
            if(puentes->tamanio > 0 && buscar_nodo_puente(puentes,puente_random) != NULL)
            {
                agregar_carro_prioridad(carro, buscar_nodo_puente(puentes,puente_random)->carros_izquierda);
            }
            else
            {
                agregar_carro_prioridad(carro, buscar_nodo_thread(threads,puente_random)->puente->carros_izquierda);
            }

        }
        else        // Derecha
        {
            carro->lado_izquierdo = 0;
            if(puentes->tamanio > 0 && buscar_nodo_puente(puentes,puente_random) != NULL)
            {
                agregar_carro_prioridad(carro, buscar_nodo_puente(puentes,puente_random)->carros_derecha);
            }
            else
            {
                agregar_carro_prioridad(carro, buscar_nodo_thread(threads,puente_random)->puente->carros_derecha);
            }

        }

        Thread thread_nuevo = (Thread) calloc(1, sizeof(struct thread));
        thread_nuevo->puente=NULL;
        thread_nuevo->carro=carro;
        thread_nuevo->prioridad = carro->prioridad;
        thread_nuevo->calendarizador=calendarizador;
        thread_nuevo->thread_identificador=i;

        if(calendarizador == 3)             // Si se esta trabajando con Priority Queue
        {
            agregar_thread_prioridad(thread_nuevo, threads);
        }
        else
        {
            agregar_thread(thread_nuevo,threads);
        }



        if(puentes->tamanio > 0 && buscar_nodo_puente(puentes,puente_random) != NULL)
        {
            pthread_create(&carro_thread, NULL, controlador_carros_jungla, (void *) carro);
        }
        else
        {
            pthread_create(&carro_thread, NULL, controlador_carros, (void *) carro);
        }

        //pthread_join(carro_thread, NULL);

        usleep(1000000);//usleep(600000); para regular          usleep(1000000); para semaforo
        i++;
    }
}



int main()
{

    threads = (ThreadList) calloc(1, sizeof(struct thread_list));   // Inicializo una lista con todos los threads puentes y carros
    threads -> tamanio = 0;

    puentes = (ThreadListPuente) calloc(1, sizeof(struct thread_list_puente));
    puentes->tamanio = 0;

    calendarizador = getParameterValueConfig("config_global.txt","calendarizador");

    switch (calendarizador )
    {
    case 0:
        printf(ANSI_COLOR_YELLOW "Utilizando Round Robin para calendarizar\n" ANSI_COLOR_RESET);
        pthread_create(&thread_calendarizador, NULL, calendarizador_RoundRobin, NULL);    // Se debe crear primero para poder ordenar el sistema
        break;
    case 1:
        printf(ANSI_COLOR_YELLOW "Utilizando FCFS para calendarizar\n" ANSI_COLOR_RESET);
        pthread_create(&thread_calendarizador, NULL, calendarizador_fcfs, NULL);    // Se debe crear primero para poder ordenar el sistema
        break;
    case 2:
        printf(ANSI_COLOR_YELLOW "Utilizando SJF para calendarizar\n" ANSI_COLOR_RESET);

        break;
    case 3:
        printf(ANSI_COLOR_YELLOW "Utilizando Priority Queue para calendarizar\n" ANSI_COLOR_RESET);
        pthread_create(&thread_calendarizador, NULL, calendarizador_priority_queue, NULL);    // Se debe crear primero para poder ordenar el sistema

        break;
    case 4:
        printf(ANSI_COLOR_YELLOW "Utilizando Real Time para calendarizar\n" ANSI_COLOR_RESET);
        break;
    default:
        printf(ANSI_COLOR_YELLOW "Utilizando Round Robin para calendarizar\n" ANSI_COLOR_RESET);
        pthread_create(&thread_calendarizador, NULL, calendarizador_RoundRobin, NULL);    // Se debe crear primero para poder ordenar el sistema
        break;
    }



    /* PUENTE 0 */
    Thread_Puente puente_creado_0 = crear_puente_0();
    pthread_t thread_puente_0;           // Creo la instancia del thread del puente

    if(puente_creado_0->control == JUNGLA)
    {

        agregar_puente(puente_creado_0, puentes);
    }
    else
    {
        Thread thread_nuevo = (Thread) calloc(1, sizeof(struct thread));   // Creo un nodo thread el cual puede ser carro o puente
        thread_nuevo->puente=puente_creado_0;
        thread_nuevo->carro=NULL;
        thread_nuevo->prioridad=-1;               // Solo me interesa en este caso el thread de carro
        thread_nuevo->calendarizador=calendarizador;
        thread_nuevo->thread_identificador=0;
        agregar_thread(thread_nuevo,threads);           // Agrego el thread puente a la lista de threads


        switch (puente_creado_0->control)
        {
        case OFICIAL:
            pthread_create(&thread_puente_0, NULL, algoritmo_puente_oficial, (void *) puente_creado_0);
            break;
        case SEMAFORO:

            pthread_create(&thread_puente_0, NULL, algoritmo_puente_semaforo, (void *) puente_creado_0);
            break;
        default:
            pthread_create(&thread_puente_0, NULL, algoritmo_puente_oficial, (void *) puente_creado_0);
            break;
        }

    }


    /* PUENTE 1 */
    Thread_Puente puente_creado_1 = crear_puente_1();
    pthread_t thread_puente_1;           // Creo la instancia del thread del puente

    if(puente_creado_1->control == JUNGLA)
    {
        agregar_puente(puente_creado_1, puentes);

    }
    else
    {
        Thread thread_nuevo_1 = (Thread) calloc(1, sizeof(struct thread));   // Creo un nodo thread el cual puede ser carro o puente
        thread_nuevo_1 ->puente=puente_creado_1;
        thread_nuevo_1 ->carro=NULL;
        thread_nuevo_1->prioridad=-1;                   // Solo me interesa en este caso el thread de carro
        thread_nuevo_1 ->calendarizador=calendarizador;
        thread_nuevo_1 ->thread_identificador=1;
        agregar_thread(thread_nuevo_1,threads);            // Agrego el thread puente a la lista de threads



        switch (puente_creado_1->control)
        {
        case OFICIAL:
            pthread_create(&thread_puente_1, NULL, algoritmo_puente_oficial, (void *) puente_creado_1);
            break;
        case SEMAFORO:
            pthread_create(&thread_puente_1, NULL, algoritmo_puente_semaforo, (void *) puente_creado_1);
            break;
        default:
            pthread_create(&thread_puente_1, NULL, algoritmo_puente_oficial, (void *) puente_creado_1);
            break;
        }

    }


    /* PUENTE 2 */
    Thread_Puente puente_creado_2 = crear_puente_2();
    pthread_t thread_puente_2;           // Creo la instancia del thread del puente

    if(puente_creado_2->control == JUNGLA)
    {
        agregar_puente(puente_creado_2, puentes);

    }
    else
    {

        Thread thread_nuevo_2 = (Thread) calloc(1, sizeof(struct thread));   // Creo un nodo thread el cual puede ser carro o puente
        thread_nuevo_2->puente=puente_creado_2;
        thread_nuevo_2->carro=NULL;
        thread_nuevo_2->prioridad=-1;                  // Solo me interesa en este caso el thread de carro
        thread_nuevo_2->calendarizador=calendarizador;
        thread_nuevo_2->thread_identificador=2;
        agregar_thread(thread_nuevo_2,threads);           // Agrego el thread puente a la lista de threads


        switch (puente_creado_2->control)
        {
        case OFICIAL:
            pthread_create(&thread_puente_2, NULL, algoritmo_puente_oficial, (void *) puente_creado_2);
            break;
        case SEMAFORO:
            pthread_create(&thread_puente_2, NULL, algoritmo_puente_semaforo, (void *) puente_creado_2);
            break;
        default:
            pthread_create(&thread_puente_2, NULL, algoritmo_puente_oficial, (void *) puente_creado_2);
            break;
        }

    }


    /* PUENTE 3 */
    Thread_Puente puente_creado_3 = crear_puente_3();
    pthread_t thread_puente_3;
    if(puente_creado_3->control == JUNGLA)
    {
        agregar_puente(puente_creado_3, puentes);
    }
    else
    {
        Thread thread_nuevo_3 = (Thread) calloc(1,sizeof(struct thread));   // Creo un nodo thread el cual puede ser carro o puente
        thread_nuevo_3->puente=puente_creado_3;
        thread_nuevo_3->carro=NULL;
        thread_nuevo_3->prioridad=-1;                   // Solo me interesa en este caso el thread de carro
        thread_nuevo_3->calendarizador=calendarizador;
        thread_nuevo_3->thread_identificador=3;
        agregar_thread(thread_nuevo_3,threads);           // Agrego el thread puente a la lista de threads


        // Creo la instancia del thread del puente
        switch (puente_creado_3->control)
        {
        case OFICIAL:
            pthread_create(&thread_puente_3, NULL, algoritmo_puente_oficial, (void *) puente_creado_3);
            break;
        case SEMAFORO:
            pthread_create(&thread_puente_3, NULL, algoritmo_puente_semaforo, (void *) puente_creado_3);
            break;
        default:
            pthread_create(&thread_puente_3, NULL, algoritmo_puente_oficial, (void *) puente_creado_3);
            break;
        }

    }


    if (pthread_mutex_init(&lock_thread_terminado, NULL) != 0)
    {
        printf("\n mutex init failed\n");
    }


    if (pthread_mutex_init(&lock_thread_actual, NULL) != 0)
    {
        printf("\n mutex init failed\n");
    }

    if (pthread_mutex_init(&lock_contador_tmp, NULL) != 0)
    {
        printf("\n mutex init failed\n");
    }

    if (pthread_mutex_init(&lock_carro_movimiento, NULL) != 0)
    {
        printf("\n mutex init failed\n");
    }

    if(pthread_mutex_init(&lock_modificar_lista, NULL) != 0)
    {
        printf("\n mutex init failed\n");
    }

    if(pthread_mutex_init(&lock_comenzar_espera, NULL) != 0)
    {
        printf("\n mutex init failed\n");
    }

    if(pthread_mutex_init(&lock_agregarse, NULL) != 0)
    {
        printf("\n mutex init failed\n");
    }


    // Por ultimo comienzo la ejecucion del hilo y su respectivo join
    pthread_create(&thread_generador_carros, NULL, generador_carros, NULL);


    if(puente_creado_0->control != JUNGLA)
    {
        pthread_join(thread_puente_0, NULL);
    }
    if(puente_creado_1->control != JUNGLA)
    {
        pthread_join(thread_puente_1, NULL);
    }
    if(puente_creado_2->control != JUNGLA)
    {
        pthread_join(thread_puente_2, NULL);
    }
    if(puente_creado_3->control != JUNGLA)
    {
        pthread_join(thread_puente_3, NULL);
    }


    pthread_join(thread_calendarizador, NULL);
    pthread_join(thread_generador_carros, NULL);

    pthread_mutex_destroy(&lock_thread_terminado);
    pthread_mutex_destroy(&lock_thread_actual);
    pthread_mutex_destroy(&lock_contador_tmp);
    pthread_mutex_destroy(&lock_carro_movimiento);
    pthread_mutex_destroy(&lock_modificar_lista);
    pthread_mutex_destroy(&lock_comenzar_espera);
    pthread_mutex_destroy(&lock_agregarse);
    return 0;

}

