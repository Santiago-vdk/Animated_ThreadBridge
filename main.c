#include <stdio.h>
#include <stdlib.h>
#include "mythreads/mythread.h"
#include "thread_data.h"
#include <time.h>
#include "puentes.h"


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int thread_actual = -1;
int thread_terminado = 1;
int calendarizador = -1;

pthread_t thread_calendarizador;
pthread_t thread_generador_carros;

pthread_mutex_t lock_thread_terminado;
pthread_mutex_t lock_thread_actual;
pthread_mutex_t lock_contador_tmp;
pthread_mutex_t lock_carro_movimiento;
pthread_mutex_t lock_modificar_lista;

ThreadList threads;

void *calendarizador_RoundRobin(void *t)
{
    Thread temporal = threads->head;
    int Quantum = 2;
    int QuantumTmp = 0;
    while(1)
    {
        if(threads->head != NULL)
        {

            pthread_mutex_lock(&lock_thread_actual);
            QuantumTmp = Quantum;
            thread_actual = temporal->thread_identificador;
            pthread_mutex_unlock(&lock_thread_actual);


            pthread_mutex_lock(&lock_thread_terminado);
            thread_terminado = 0;
            printf(ANSI_COLOR_RED "\nComenzando a ejecutar hilo %d\n" ANSI_COLOR_RESET, thread_actual);
            pthread_mutex_unlock(&lock_thread_terminado);

            if(thread_actual > 4)
            {
                if(buscar_nodo_thread(threads,thread_actual)->carro->corriendo == 0)
                {
                    //printf(ANSI_COLOR_YELLOW "Desperdicion\n" ANSI_COLOR_RESET);
                }
                else
                {
                    while(QuantumTmp > 0)
                    {
                        QuantumTmp--;
                        usleep(100);
                    }
                }
            }
            else
            {
                while(QuantumTmp > 0)
                {
                    QuantumTmp--;
                    usleep(100);
                }
            }

            if(temporal->next != NULL)
            {
                QuantumTmp = Quantum;
                temporal = temporal->next;      // Obtengo el siguiente
            }
            else
            {
                printf("Llegue al final de la cola \n");
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
            pthread_mutex_lock(&lock_thread_actual);
            thread_actual = temporal->thread_identificador;
            pthread_mutex_unlock(&lock_thread_actual);


            pthread_mutex_lock(&lock_thread_terminado);
            thread_terminado = 0;
            printf(ANSI_COLOR_RED "\nComenzando a ejecutar hilo %d\n" ANSI_COLOR_RESET, thread_actual);
            pthread_mutex_unlock(&lock_thread_terminado);


            while (thread_terminado == 0)
            {
                //printf("Thread con id %d corriendo \n", thread_corriendo->thread_identificador);
            }

            if(buscar_nodo_thread(threads,thread_actual) != NULL)
            {
                //printf(ANSI_COLOR_YELLOW "Pop out & push in \n" ANSI_COLOR_RESET);
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
            printf("No hay hilos para calendarizar \n");
        }
        usleep(100000);
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
                    printf("Trafico dejo pasar sus %d carros izquierda\n", temporal_k_izquierda);
                    //temporal_k_izquierda = 0;
                    thread_terminado = 1;
                    pthread_mutex_unlock(&lock_thread_terminado);
                    break;

                }

                if (data->ocupancia == data->capacidad)         // Puente lleno
                {
                    printf(ANSI_COLOR_CYAN "Puente lleno, haciendo esperar a los carros de la izquierda  \n" ANSI_COLOR_RESET);
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


                        printf(ANSI_COLOR_GREEN "Agregando carro %lu a circulacion sobre puente \n" ANSI_COLOR_RESET, tmp->thread_identificador);
                        data->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad
                        temporal_k_izquierda += 1;
                        pthread_mutex_unlock(&lock_contador_tmp);

                    }
                    else
                    {
                        pthread_mutex_lock(&lock_thread_terminado);
                        printf("No hay carros a la izquierda del puente \n");
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
                        printf("Trafico dejo pasar sus %d carros derecha\n", temporal_k_derecha);
                        temporal_k_derecha = 0;             // Reinicio temporal
                        temporal_k_izquierda = 0;           // Reinicio temporal
                        thread_terminado = 1;
                        pthread_mutex_unlock(&lock_thread_terminado);
                        break;

                    }

                    if (data->ocupancia == data->capacidad)         // Puente lleno
                    {
                        printf(ANSI_COLOR_CYAN "Puente lleno, haciendo esperar a los carros de la derecha  \n" ANSI_COLOR_RESET);
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


                            printf(ANSI_COLOR_MAGENTA "Agregando carro %lu a circulacion sobre puente \n" ANSI_COLOR_RESET, tmp->thread_identificador);
                            data->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad
                            temporal_k_derecha += 1;
                            pthread_mutex_unlock(&lock_contador_tmp);

                        }
                        else
                        {
                            pthread_mutex_lock(&lock_thread_terminado);
                            printf("No hay carros a la derecha del puente \n");
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

void *esperar_semaforo(int tiempo){

}

void *algoritmo_puente_semaforo(void *puente)
{
    Thread_Puente data = (Thread_Puente) puente;
    int temporal_semaforo_izquierda = data->tiempo_semaforo_izquierda;
    int temporal_semaforo_derecha = data->tiempo_semaforo_derecha;
    int temporal_semaforo_amarillo = 2;

    int semaforo_izquierda = data->semaforo_izquierda;
    int semaforo_derecha = data->semaforo_derecha;
    int semaforo_amarillo = 0;          // Este parametro es inteligente y decide cuando esperar y cuando no

    while(1)
    {
        if(thread_actual == data->thread_identificador && thread_terminado == 0)
        {
           /* while(temporal_semaforo_amarillo > 0)   // Se utiliza para prevenir que se pierda demasiado tiempo de procesamiento cuando se lleno el puente y el otro semaforo debe esperar que se vacie
            {
                temporal_semaforo_amarillo --;
                sleep(1);
            }*/

            if(data->semaforo_izquierda = 1)        // el izquierdo esta encendido en verde
            {

                while(temporal_semaforo_izquierda > 0)          // Mientras no se haya acabado el contador dejo pasar los carros
                {

                    if (data->ocupancia == data->capacidad)         // Puente lleno
                    {
                        printf(ANSI_COLOR_CYAN "Puente lleno, haciendo esperar a los carros de la izquierda, desperdicio semaforo  \n" ANSI_COLOR_RESET);
                        semaforo_amarillo = 0;
                        break;
                    }
                    else            // Si habia espacio
                    {

                        if((data->carros_izquierda->tamanio > 0) && (data->ocupancia < data->capacidad))
                        {

                            Thread_Carro tmp = pop_primer_thread_carro(data->carros_izquierda); // Extraigo la cabeza de la lista del lado izquierdo y reordeno
                            agregar_carro(tmp,data->carros_circulando);     // Paso el thread a los que estan circulando

                            pthread_mutex_lock(&lock_contador_tmp);
                            buscar_nodo_thread(threads,tmp->thread_identificador)->carro->corriendo = 1; // Poner a caminar el carro

                            printf(ANSI_COLOR_GREEN "Agregando carro %lu a circulacion sobre puente \n" ANSI_COLOR_RESET, tmp->thread_identificador);
                            data->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad

                            semaforo_amarillo = 1;          // Requiero esperar que terminen de pasar algunos carros de mi lado
                            pthread_mutex_unlock(&lock_contador_tmp);

                        }
                        else
                        {
                            pthread_mutex_lock(&lock_thread_terminado);
                            printf("No hay carros a la izquierda del puente \n");
                            thread_terminado = 1;
                            semaforo_amarillo = 0;                  // No es necesario esperar a que pasen los carros
                            pthread_mutex_unlock(&lock_thread_terminado);
                            break;
                        }



                    }

                    temporal_semaforo_izquierda --;
                    sleep(1);
                }




                temporal_semaforo_amarillo = 2;
                semaforo_izquierda = 0;         // Cambiar izquierda a verde
                semaforo_derecha = 1;           // cambiar derecha a rojo
                temporal_semaforo_izquierda = data->tiempo_semaforo_izquierda;  // Reinicio para estar seguro de que se volvera a ejecutar completamente
                temporal_semaforo_derecha = data->tiempo_semaforo_derecha;

            }
            else                                        // Semaforo de la derecha en verde
            {

                while(temporal_semaforo_derecha > 0)
                {

                    if (data->ocupancia == data->capacidad)         // Puente lleno
                    {
                        printf(ANSI_COLOR_CYAN "Puente lleno, haciendo esperar a los carros de la derecha, desperdicio semaforo  \n" ANSI_COLOR_RESET);
                        semaforo_amarillo = 0;
                        break;
                    }
                    else            // Si habia espacio
                    {


                        if((data->carros_derecha->tamanio > 0) && (data->ocupancia < data->capacidad))
                        {

                            Thread_Carro tmp = pop_primer_thread_carro(data->carros_derecha); // Extraigo la cabeza de la lista del lado izquierdo y reordeno
                            agregar_carro(tmp,data->carros_circulando);     // Paso el thread a los que estan circulando

                            pthread_mutex_lock(&lock_contador_tmp);
                            buscar_nodo_thread(threads,tmp->thread_identificador)->carro->corriendo = 1; // Poner a caminar el carro


                            printf(ANSI_COLOR_MAGENTA "Agregando carro %lu a circulacion sobre puente \n" ANSI_COLOR_RESET, tmp->thread_identificador);
                            data->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad
                            semaforo_amarillo = 1;
                            pthread_mutex_unlock(&lock_contador_tmp);

                        }
                        else
                        {
                            pthread_mutex_lock(&lock_thread_terminado);
                            printf("No hay carros a la derecha del puente \n");
                            thread_terminado = 1;
                            semaforo_amarillo = 0;              // No requiero esperar a que pasen algunos
                            pthread_mutex_unlock(&lock_thread_terminado);

                            break;
                        }


                    }


                    temporal_semaforo_derecha --;
                    sleep(1);
                }

                temporal_semaforo_amarillo = 2;
                semaforo_izquierda = 1;         // Cambiar izquierda a verde
                semaforo_derecha = 0;           // cambiar derecha a rojo
                temporal_semaforo_izquierda = data->tiempo_semaforo_izquierda;
                temporal_semaforo_derecha = data->tiempo_semaforo_derecha;

            }
        }
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

                        printf("Carro %d termino de pasar el puente, no habia nadie en frente %d\n", data->thread_identificador, puente_tmp->carros_circulando->tamanio);

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

                        printf("Carro %d termino de pasar el puente, habia alguien en frente %d\n", data->thread_identificador, puente_tmp->carros_circulando->tamanio);


                        eliminar_nodo_thread(threads,data->thread_identificador);           // Elimino el carro de la lista de hilos
                        eliminar_nodo_carro(buscar_nodo_thread(threads,data->puente)->puente->carros_circulando,data->thread_identificador);    // Elimino el carro de la lista de los carros circulando de su debido puente
                        buscar_nodo_thread(threads,data->puente)->puente->ocupancia -= 1;


                        thread_terminado = 1;
                        pthread_mutex_unlock(&lock_thread_terminado);

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

// Utiliza la lista global de los hilos para encontrar el puente en el que tiene que insertar carros
void *generador_carros(void *t)
{
    int i = 4;
    //pthread_t array [10000];

    while(1)
    {
        srand(time(NULL));
        //printf("Generando carro de tipo CARRO al lado izquierdo del puente 0 \n");

        int puente_random = rand() % 4;
        int lado_random = rand() % 3;
        // Se agrega el carro a la lista que le corresponde, sea izquierdo o derecho
        Thread_Carro carro = (Thread_Carro) malloc(sizeof(struct thread_carro));
        carro->thread_identificador = i;
        carro -> tipo_carro = CARRO;
        carro -> limite_tiempo = NULL;
        carro -> corriendo = 0;
        carro -> vida_carro = NULL;
        carro -> puente = puente_random;

        carro -> velocidad = 0.2;
        carro -> prioridad = 2;         // Por ser carro regular

        pthread_t carro_thread;
        //carro -> hilo = carro_thread;

        if(lado_random == 0)
        {

            // Si se trabaja con cola de prioridad es necesario ordenar los carros por prioridad
            if(calendarizador == 3)
            {
                agregar_thread_priority(carro, buscar_nodo_thread(threads,puente_random)->puente->carros_izquierda);

            }
            else
            {
                agregar_carro(carro, buscar_nodo_thread(threads,puente_random)->puente->carros_izquierda);   // Agrego el carro a ese lado

            }

        }
        else
        {

            // Si se trabaja con cola de prioridad es necesario ordenar los carros por prioridad
            if(calendarizador == 3)
            {
                agregar_thread_priority(carro, buscar_nodo_thread(threads,puente_random)->puente->carros_derecha);

            }
            else
            {
                agregar_carro(carro, buscar_nodo_thread(threads,puente_random)->puente->carros_derecha);   // Agrego el carro a ese lado

            }

        }

        Thread thread_nuevo = (Thread) malloc(sizeof(struct thread));
        thread_nuevo->puente=NULL;
        thread_nuevo->carro=carro;
        thread_nuevo->calendarizador=FCFS;
        thread_nuevo->thread_identificador=i;

        agregar_thread(thread_nuevo,threads);
        //array[i] = carro_thread;
        pthread_create(&carro_thread, NULL, controlador_carros, (void *) carro);
        //pthread_join(carro_thread, NULL);


        usleep(500000);
        i++;
    }

    /*  int j = 4;
      while(j < i){
          pthread_t tmp = array[j];
          pthread_join(tmp, NULL);
          j++;
      }*/
}



int main()
{
    threads = (ThreadList) malloc(sizeof(struct thread_list));   // Inicializo una lista con todos los threads puentes y carros
    threads -> tamanio = 0;

    calendarizador =atoi(getParameterValueConfig("config_global.txt","calendarizador"));
    if(calendarizador == NULL)
    {
        printf("Error leyendo configuracion global\n");
        exit(EXIT_FAILURE);
    }

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

    Thread thread_nuevo = (Thread) malloc(sizeof(struct thread));   // Creo un nodo thread el cual puede ser carro o puente
    thread_nuevo->puente=puente_creado_0;
    thread_nuevo->carro=NULL;                   // Solo me interesa en este caso el thread de carro
    thread_nuevo->calendarizador=calendarizador;
    thread_nuevo->thread_identificador=0;
    agregar_thread(thread_nuevo,threads);           // Agrego el thread puente a la lista de threads

    pthread_t thread_puente_0;           // Creo la instancia del thread del puente
    pthread_create(&thread_puente_0, NULL, algoritmo_puente_semaforo, (void *) puente_creado_0);


    /* PUENTE 1 */
    Thread_Puente puente_creado_1 = crear_puente_1();

    Thread thread_nuevo_1 = (Thread) malloc(sizeof(struct thread));   // Creo un nodo thread el cual puede ser carro o puente
    thread_nuevo_1 ->puente=puente_creado_1;
    thread_nuevo_1 ->carro=NULL;                   // Solo me interesa en este caso el thread de carro
    thread_nuevo_1 ->calendarizador=calendarizador;
    thread_nuevo_1 ->thread_identificador=1;
    agregar_thread(thread_nuevo_1,threads);            // Agrego el thread puente a la lista de threads

    pthread_t thread_puente_1;           // Creo la instancia del thread del puente
    pthread_create(&thread_puente_1, NULL, algoritmo_puente_semaforo, (void *) puente_creado_1);


    /* PUENTE 2 */
    Thread_Puente puente_creado_2 = crear_puente_2();

    Thread thread_nuevo_2 = (Thread) malloc(sizeof(struct thread));   // Creo un nodo thread el cual puede ser carro o puente
    thread_nuevo_2->puente=puente_creado_2;
    thread_nuevo_2->carro=NULL;                   // Solo me interesa en este caso el thread de carro
    thread_nuevo_2->calendarizador=calendarizador;
    thread_nuevo_2->thread_identificador=2;
    agregar_thread(thread_nuevo_2,threads);           // Agrego el thread puente a la lista de threads

    pthread_t thread_puente_2;           // Creo la instancia del thread del puente
    pthread_create(&thread_puente_2, NULL, algoritmo_puente_semaforo, (void *) puente_creado_2);


    /* PUENTE 3 */
    Thread_Puente puente_creado_3 = crear_puente_3();

    Thread thread_nuevo_3 = (Thread) malloc(sizeof(struct thread));   // Creo un nodo thread el cual puede ser carro o puente
    thread_nuevo_3->puente=puente_creado_3;
    thread_nuevo_3->carro=NULL;                   // Solo me interesa en este caso el thread de carro
    thread_nuevo_3->calendarizador=calendarizador;
    thread_nuevo_3->thread_identificador=3;
    agregar_thread(thread_nuevo_3,threads);           // Agrego el thread puente a la lista de threads

    pthread_t thread_puente_3;           // Creo la instancia del thread del puente
    pthread_create(&thread_puente_3, NULL, algoritmo_puente_semaforo, (void *) puente_creado_3);


    // Por ultimo comienzo la ejecucion del hilo y su respectivo join
    pthread_create(&thread_generador_carros, NULL, generador_carros, NULL);

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



    pthread_join(thread_puente_0, NULL);
    pthread_join(thread_puente_1, NULL);
    pthread_join(thread_puente_2, NULL);
    pthread_join(thread_puente_3, NULL);

    pthread_join(thread_calendarizador, NULL);
    pthread_join(thread_generador_carros, NULL);

    pthread_mutex_destroy(&lock_thread_terminado);
    pthread_mutex_destroy(&lock_thread_actual);
    pthread_mutex_destroy(&lock_contador_tmp);
    pthread_mutex_destroy(&lock_carro_movimiento);
    pthread_mutex_destroy(&lock_modificar_lista);
    return 0;

}

