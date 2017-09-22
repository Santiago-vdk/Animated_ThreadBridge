#include <stdio.h>
#include <stdlib.h>
#include "mythreads/mythread.h"
#include "thread_data.h"

#include <time.h>

int thread_actual = -1;
int thread_terminado = 0;

pthread_t thread_calendarizador;
pthread_t thread_generador_carros;

ThreadList threads;     // Todos los threads

void *calendarizador_fcfs(void *t)
{
    while(1)
    {
        printf("Calendarizando FCFS \n");

        if(threads->head != NULL)
        {
            if(thread_terminado == 0)
            {
                for(int i =0; i < threads->tamanio; i++)
                {
                    //Thread tmp = buscar_nodo_thread(threads,i);
                    thread_actual = i;
                }
            }
            else
            {
                printf("Esperando que thread actual termine \n");
            }


        }
        else
        {
            printf("No hay hilos para calendarizar \n");
        }

        sleep(1);



    }

}

void *controlador_carros(void *carro)
{


    Thread_Carro data = (Thread_Carro) carro;

    while(1)
    {
        if(thread_actual == data->thread_identificador)
        {
            printf("Carro %lu moviendose \n", data->thread_identificador);
            thread_terminado = 1;
        }
        sleep(data->velocidad);
    }

}


void *algoritmo_puente_oficial(void *puente)
{
    Thread_Puente data = (Thread_Puente) puente;

    while(1)
    {
        if(thread_actual == data->thread_identificador)
        {
            printf("Ejecutando algoritmo de puente con metodo del oficial\n");

            // Proceso lado izquierdo
            for (int carros_izq = 0; carros_izq < data->k; carros_izq++)
            {
                // Puente lleno
                if (data->ocupancia == data->capacidad)
                {
                    printf("Esperando que terminen carros del lado derecho \n");
                }
                // Puente con campo
                else
                {
                    if(data->carros_izquierda->tamanio > 0)
                    {
                        printf("Agregando carro a circulacion \n");
                        Thread_Carro tmp = buscar_nodo_carro(data->carros_izquierda, carros_izq);       // Posible problema
                        tmp-> corriendo = 1;
                        eliminar_nodo_carro(data->carros_izquierda, carros_izq);
                        agregar_carro(data->carros_circulando, tmp);
                        data->ocupancia = data->ocupancia + 1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad
                    }
                    else
                    {
                        printf("No hay carros a la izquierda del puente \n");
                    }


                }
            }



            sleep(1);
        }
        // No es necesario el sleep porque busca ejecutar t

    }
}


void *algoritmo_puente_semaforo(void *t)
{
    while(1)
    {
        printf("Ejecutando algoritmo de puente con metodo del semaforo\n");
        sleep(2);
    }
}

void *algoritmo_puente_leyjungla(void *t)
{
    while(1)
    {
        printf("Ejecutando algoritmo de puente con metodo de la ley de la jungla\n");
        sleep(2);
    }
}


// Utiliza la lista global de los hilos para encontrar el puente en el que tiene que insertar carros
void *generador_carros(void *t)
{
    int i = 0;

    while(1)
    {

        printf("Generando carro de tipo CARRO al lado izquierdo del puente 0 \n");
        // Se agrega el carro a la lista que le corresponde, sea izquierdo o derecho
        Thread_Carro carro = (Thread_Carro) malloc(sizeof(struct thread_carro));
        carro->thread_identificador = i;
        carro -> calendarizador=FCFS;
        carro -> tipo_carro = CARRO;
        carro -> limite_tiempo = NULL;
        carro -> corriendo = 0;
        carro -> vida_carro = NULL;
        carro -> puente = 0;
        carro -> next = NULL;
        carro -> velocidad = 4;

        pthread_t carro_thread;
        carro -> hilo = carro_thread;

        //Thread_Puente puente_tmp = buscar_nodo_thread_puente(threads,0);       // Selecciono el primer puente (0) de la lista global
        // ThreadListCarro lado_izq_tmp = puente_tmp->carros_izquierda;   // Selecciono el lado izquierdo del puente 0
        agregar_carro(carro, buscar_nodo_thread_puente(threads,0)->puente->carros_izquierda);                                   // Agrego el carro a ese lado


        pthread_create(&carro_thread, NULL, controlador_carros, (void *) carro);
        pthread_join(carro_thread, NULL);


        sleep(2);
        i++;
    }
}

void leer_config_puente_0()
{


    FILE* fp;
    char buffer[255];

    fp = fopen("config_puente_0.txt", "r");

    while(fgets(buffer, 255, (FILE*) fp))
    {
        printf(buffer);
    }

    fclose(fp);


}


int main()
{

    //leer_config_puente_0();         // Lee e instancia cada puente
    //leer_config_puente_1();         // Lee e instancia cada puente
    //leer_config_puente_2();         // Lee e instancia cada puente
    //leer_config_puente_3();         // Lee e instancia cada puente

    threads = (ThreadList) malloc(sizeof(struct thread_list));              // Inicializo una lista con todos los threads puentes y carros

    pthread_create(&thread_calendarizador, NULL, calendarizador_fcfs, NULL);


    Thread_Puente oficial_puente_0 = (Thread_Puente) malloc(sizeof(struct thread_puente));
    oficial_puente_0 ->calendarizador=0;

    oficial_puente_0 -> thread_identificador = 0;              // El id de los threads en los puentes es fijo
    oficial_puente_0 -> puente_id = 0;             // identificador del puente, para los puentes es el mismo que el id de thread
    oficial_puente_0 -> ocupancia = 0;             // Cantidad de carros que estan en el puente transitando
    oficial_puente_0 -> capacidad = 4;              // Capacidad, numero de carros en el puente al mismo tiempo
    oficial_puente_0 -> control = OFICIAL;            // Algoritmo de control del puente
    oficial_puente_0 -> k = 5;
    oficial_puente_0 -> carros_circulando = malloc(sizeof(struct thread_list));     // Contiene todos los threads de carros del puente
    oficial_puente_0 -> carros_izquierda = malloc(sizeof(struct thread_list));
    oficial_puente_0 -> carros_derecha = malloc(sizeof(struct thread_list));
    oficial_puente_0 -> next = NULL;

    pthread_t thread_puente_0;           // Creo la instancia del thread del puente
    oficial_puente_0->hilo=thread_puente_0;         // Referencio esa instancia al objeto del puente para poder controlar aspectos del hilo

    Thread thread_nuevo = (Thread) malloc(sizeof(struct thread));   // Creo un nodo thread el cual puede ser carro o puente
    thread_nuevo->puente=oficial_puente_0;
    thread_nuevo->carro=NULL;                   // Solo me interesa en este caso el thread de carro
    agregar_thread(thread_nuevo,threads);           // Agrego el thread puente a la lista de threads


    // Por ultimo comienzo la ejecucion del hilo y su respectivo join
    pthread_create(&thread_puente_0, NULL, algoritmo_puente_oficial, (void *) oficial_puente_0);
    pthread_create(&thread_generador_carros, NULL, generador_carros, NULL);

    pthread_join(thread_puente_0, NULL);
    pthread_join(thread_calendarizador, NULL);
    // pthread_join(thread_generador_carros, NULL);

    return 0;

}

