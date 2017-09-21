#include <stdio.h>
#include <stdlib.h>
#include "mythreads/mythread.h"
#include "thread_data.h"

#include <time.h>


ThreadList carros;              // Lista global de carros
ThreadList puente_1_izq;        // Instancia para carros del lado izquierdo del puente 1
ThreadList puente_1_der;        // Instancia para carros del lado derecho del puente 1

pthread_t controlador;                 // Instancia del Thread principal para la generacion de vehiculos
pthread_t generador;
pthread_t thread_id[NUM_THREADS];
pthread_t puentes[4];           // Instancia de cada uno de los Threads de puentes


void *calendarizador(void *t)
{
    printf("Calendarizando \n");

}


void *controlador_carros(void *t)
{
    printf("Controlando carros \n");
}

int numero_random_lado()
{
    srand ( time(NULL) );
    int result = 0;
    result = rand() % 2;
    return(result);      // Random entre 0(izquierda) y 1(derecha)
}

int numero_random_tipo()
{
    srand ( time(NULL) );
    return(rand() % 3);      // Random entre 0(izquierda) y 1(derecha)
}

void *controlador_puentes(void *t)
{
    printf("Controlando puentes \n");

}
void *generador_carros(void *t)
{
    int i = 0;
    if(i==NUM_THREADS) printf("# max de threads");
    while(i<NUM_THREADS)
    {
        int lado_puente = numero_random_lado();

        if(lado_puente == 0)
        {
            int tipo_carro = numero_random_tipo();
            Thread_Carro_Puente carro = (Thread_Carro_Puente) malloc(sizeof(struct thread_data));
            carro -> thread_id=i;
            carro -> puente = i;
            carro -> calendarizador=RR;
            carro -> next = NULL;

            if(tipo_carro == CARRO)
            {
                carro->tipo = CARRO;
            }
            else if(tipo_carro == RADIOACTIVO)
            {
                carro->tipo = RADIOACTIVO;
                carro -> limite_tiempo = 10; // Segundos para que explote
            }
            else
            {
                carro->tipo = AMBULANCIA;
            }

            add_node(carro,carros);                         // Se agrega a la lista global de carros para poder actualizarle a todos el tiempo
            pthread_create(&thread_id[i], NULL,  controlador_carros, (void *) carro);       // Thread que controla el tiempo de cada carro por si solo


            // Se agrega el carro a la lista que le corresponde, sea izquierdo o derecho
            Thread_Carro_Puente carro_puente = (Thread_Carro_Puente) malloc(sizeof(struct thread_data));
            carro_puente -> thread_id=i;
            carro_puente -> puente = i;
            carro_puente -> calendarizador=RR;
            carro_puente -> next = NULL;


            if(tipo_carro == CARRO)
            {
                carro_puente->tipo = CARRO;
            }
            else if(tipo_carro == RADIOACTIVO)
            {
                carro_puente->tipo = RADIOACTIVO;
                carro_puente -> limite_tiempo = 10; // Segundos para que explote
            }
            else
            {
                carro_puente->tipo = AMBULANCIA;
            }

            add_node(carro_puente,puente_1_izq);
            printf("Generando carro de tipo %d al lado %d del puente %d \n",tipo_carro, lado_puente, i);

        }
        else
        {

            int tipo_carro = numero_random_tipo();
            Thread_Carro_Puente carro = (Thread_Carro_Puente) malloc(sizeof(struct thread_data));
            carro -> thread_id=i;
            carro -> puente = i;
            carro -> calendarizador=RR;
            carro -> next = NULL;

            if(tipo_carro == CARRO)
            {
                carro->tipo = CARRO;
            }
            else if(tipo_carro == RADIOACTIVO)
            {
                carro->tipo = RADIOACTIVO;
                carro -> limite_tiempo = 10; // Segundos para que explote
            }
            else
            {
                carro->tipo = AMBULANCIA;
            }

            add_node(carro,carros);                         // Se agrega a la lista global de carros para poder actualizarle a todos el tiempo
            pthread_create(&thread_id[i], NULL,  controlador_carros, (void *) carro);       // Thread que controla el tiempo de cada carro por si solo


            // Se agrega el carro a la lista que le corresponde, sea izquierdo o derecho
            Thread_Carro_Puente carro_puente = (Thread_Carro_Puente) malloc(sizeof(struct thread_data));
            carro_puente -> thread_id=i;
            carro_puente -> puente = i;
            carro_puente -> calendarizador=RR;
            carro_puente -> next = NULL;


            if(tipo_carro == CARRO)
            {
                carro_puente->tipo = CARRO;
            }
            else if(tipo_carro == RADIOACTIVO)
            {
                carro_puente->tipo = RADIOACTIVO;
                carro_puente -> limite_tiempo = 10; // Segundos para que explote
            }
            else
            {
                carro_puente->tipo = AMBULANCIA;
            }

            add_node(carro_puente,puente_1_der);
            printf("Generando carro de tipo %d al lado %d del puente %d \n",tipo_carro, lado_puente, i);
        }

        if(i==3)
        {
            i=0;

        }
        else
        {
            i++;
        }


        sleep(1);

    }
}




int main()
{

    carros = malloc(sizeof(struct thread_list));
    puente_1_der = malloc(sizeof(struct thread_list));
    puente_1_izq = malloc(sizeof(struct thread_list));

    Puente puente_0 = (Puente) malloc(sizeof(struct puentes));
    puente_0 -> bridge_id = 0;             // identificador del puente, para los puentes es el mismo que el id de thread
    puente_0 -> current_cars = malloc(sizeof(struct thread_list));     // Contiene todos los threads de carros del puente
    puente_0 -> occupancy = 0;             // Cantidad de carros que estan en el puente transitando
    puente_0 -> capacity = 4;              // Capacidad, numero de carros en el puente al mismo tiempo
    puente_0 -> control = OFICIAL;            // Algoritmo de control del puente
    puente_0 -> k = 9;                     // En caso de correr con algoritmo del oficial, el K define el numero de carros que pasaran por ciclo


    Puente puente_1 = (Puente) malloc(sizeof(struct puentes));
    puente_1 -> bridge_id = 0;             // identificador del puente, para los puentes es el mismo que el id de thread
    puente_1 -> current_cars = malloc(sizeof(struct thread_list));     // Contiene todos los threads de carros del puente
    puente_1 -> occupancy = 0;             // Cantidad de carros que estan en el puente transitando
    puente_1 -> capacity = 4;              // Capacidad, numero de carros en el puente al mismo tiempo
    puente_1 -> control = OFICIAL;            // Algoritmo de control del puente
    puente_1 -> k = 9;                     // En caso de correr con algoritmo del oficial, el K define el numero de carros que pasaran por ciclo


    Puente puente_2 = (Puente) malloc(sizeof(struct puentes));
    puente_2 -> bridge_id = 0;             // identificador del puente, para los puentes es el mismo que el id de thread
    puente_2 -> current_cars = malloc(sizeof(struct thread_list));     // Contiene todos los threads de carros del puente
    puente_2 -> occupancy = 0;             // Cantidad de carros que estan en el puente transitando
    puente_2 -> capacity = 4;              // Capacidad, numero de carros en el puente al mismo tiempo
    puente_2 -> control = OFICIAL;            // Algoritmo de control del puente
    puente_2 -> k = 9;                     // En caso de correr con algoritmo del oficial, el K define el numero de carros que pasaran por ciclo


    Puente puente_3 = (Puente) malloc(sizeof(struct puentes));
    puente_3 -> bridge_id = 0;             // identificador del puente, para los puentes es el mismo que el id de thread
    puente_3 -> current_cars = malloc(sizeof(struct thread_list));     // Contiene todos los threads de carros del puente
    puente_3 -> occupancy = 0;             // Cantidad de carros que estan en el puente transitando
    puente_3 -> capacity = 4;              // Capacidad, numero de carros en el puente al mismo tiempo
    puente_3 -> control = OFICIAL;            // Algoritmo de control del puente
    puente_3 -> k = 9;                     // En caso de correr con algoritmo del oficial, el K define el numero de carros que pasaran por ciclo





    // Carecen de un identificador ya que son controlados por el calendarizador del SO
    pthread_create(&controlador, NULL, calendarizador, (void *) controlador);
    pthread_create(&generador, NULL, generador_carros, (void *) generador);


    // Puente 0, siempre tendra el identificador 0
    pthread_create(&puentes[0], NULL, controlador_puentes, (void *) puente_0);

    // Puente 1, siempre tendra el identificador 1
    pthread_create(&puentes[1], NULL, controlador_puentes, (void *) puente_1);

    // Puente 2, siempre tendra el identificador 2
    pthread_create(&puentes[2], NULL, controlador_puentes, (void *) puente_2);

    // Puente 3, siempre tendra el identificador 3
    pthread_create(&puentes[3], NULL, controlador_puentes, (void *) puente_3);



    pthread_join(controlador,NULL);
    pthread_join(generador,NULL);
    pthread_join(puentes[0], NULL);
    pthread_join(puentes[1], NULL);
    pthread_join(puentes[2], NULL);
    pthread_join(puentes[3], NULL);


    /*    free_mem(carros);
        free_mem(puente_1_izq);
        free_mem(puente_1_der);

        free(carros);
        free(puente_1_izq);
        free(puente_1_der);*/

    return 0;

}

