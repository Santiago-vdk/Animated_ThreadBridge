#include <stdio.h>
#include <stdlib.h>
#include "mythreads/mythread.h"
#include "thread_data.h"

#include <time.h>


ThreadList carros;              // Lista global de carros
ThreadList lista_puentes;        // Lista global de puentes para saber a quien insertar

pthread_t controlador;                 // Instancia del Thread principal para la generacion de vehiculos
pthread_t generador;
pthread_t puentes0:           // Instancia de cada uno de los Threads de puentes


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

    while(1)
    {
        // Se agrega el carro a la lista que le corresponde, sea izquierdo o derecho
        Thread_Carro_Puente carro = (Thread_Carro_Puente) malloc(sizeof(struct thread_data));
        carro -> thread_id=i;
        carro -> calendarizador=FCFS;
        carro -> tipo = CARRO;
        carro -> puente = 0;
        carro -> limite_tiempo = NULL;
        carro -> corriendo = false;
        carro -> next = NULL;

        thread_t carro_thread;
        pthread_create(&carro_thread, NULL, controlador_carros, (void *) carro);

        carro -> thread = carro_thread;

        Puente puente_tmp = getNode(lista_puentes,0);       // Selecciono el primer puente de la lista global
        ThreadList lado_izq_tmp = puente_tmp->carros_izq;   // Selecciono el lado izquierdo del puente 0
        add_node(carro,lado_izq_tmp);                                   // Agrego el carro a ese lado
        printf("Generando carro de tipo CARRO al lado izquierdo del puente 0 \n");


        sleep(3);
        i++;
    }
}




int main()
{
    carros = malloc(sizeof(struct thread_list));

    Puente puente_0 = (Puente) malloc(sizeof(struct puentes));
    puente_0 -> bridge_id = 0;             // identificador del puente, para los puentes es el mismo que el id de thread
    puente_0 -> current_cars = malloc(sizeof(struct thread_list));     // Contiene todos los threads de carros del puente
    puente_0 -> occupancy = 0;             // Cantidad de carros que estan en el puente transitando
    puente_0 -> capacity = 4;              // Capacidad, numero de carros en el puente al mismo tiempo
    puente_0 -> control = OFICIAL;            // Algoritmo de control del puente
    puente_0 -> k = 9;                     // En caso de correr con algoritmo del oficial, el K define el numero de carros que pasaran por ciclo
    puente_0 -> tiempo_semaforo = 10;
    puente_0 -> carros_izq = malloc(sizeof(struct thread_list));
    puente_0 -> carros_der = malloc(sizeof(struct thread_list));

    // Carecen de un identificador ya que son controlados por el calendarizador del SO
   // pthread_create(&controlador, NULL, calendarizador, (void *) controlador);
    pthread_create(&generador, NULL, generador_carros, (void *) generador);


    // Puente 0, siempre tendra el identificador 0
    pthread_create(&puentes0, NULL, controlador_puentes, (void *) puente_0);




  //  pthread_join(controlador,NULL);
    pthread_join(generador,NULL);
    pthread_join(puentes0, NULL);



    /*    free_mem(carros);
        free_mem(puente_1_izq);
        free_mem(puente_1_der);

        free(carros);
        free(puente_1_izq);
        free(puente_1_der);*/

    return 0;

}

