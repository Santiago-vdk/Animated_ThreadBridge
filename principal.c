#include "principal.h"
#include "calendarizador_rr.h"
#include "calendarizador_fcfs.h"
#include "calendarizador_sjf.h"
#include "calendarizador_real_time.h"
#include "calendarizador_priority_queue.h"
#include "algoritmos_control.h"
#include "manejo_carros.h"


/*
* Metodo para instanciar los modulos principales y los puentes
*/
void ejecutar()
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
        pthread_create(&thread_calendarizador, NULL, calendarizador_sjf, NULL);    // Se debe crear primero para poder ordenar el sistema
        break;
    case 3:
        printf(ANSI_COLOR_YELLOW "Utilizando Priority Queue para calendarizar\n" ANSI_COLOR_RESET);
        pthread_create(&thread_calendarizador, NULL, calendarizador_priority_queue, NULL);    // Se debe crear primero para poder ordenar el sistema
        break;
    case 4:
        printf(ANSI_COLOR_YELLOW "Utilizando Real Time para calendarizar\n" ANSI_COLOR_RESET);
        pthread_create(&thread_calendarizador, NULL, calendarizador_real_time, NULL);    // Se debe crear primero para poder ordenar el sistema
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
        thread_nuevo->velocidad=0;
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
        thread_nuevo_1->velocidad=0;
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
        thread_nuevo_2->velocidad=0;
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
        thread_nuevo_3->velocidad=0;
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


    if(hardware==1)
    {
        pthread_join(thread_puente_hardware_0, NULL);
        pthread_join(thread_puente_hardware_1, NULL);
        pthread_join(thread_puente_hardware_2, NULL);
    }

    pthread_mutex_destroy(&lock_thread_terminado);
    pthread_mutex_destroy(&lock_thread_actual);
    pthread_mutex_destroy(&lock_contador_tmp);
    pthread_mutex_destroy(&lock_carro_movimiento);
    pthread_mutex_destroy(&lock_modificar_lista);
    pthread_mutex_destroy(&lock_comenzar_espera);
    pthread_mutex_destroy(&lock_agregarse);


}
