#include <stdio.h>
#include <stdlib.h>
#include "mythreads/mythread.h"
#include "thread_data.h"

#include <time.h>
/*

ThreadList carros;              // Lista global de carros
ThreadList puente_1_izq;        // Instancia para carros del lado izquierdo del puente 1
ThreadList puente_1_der;        // Instancia para carros del lado derecho del puente 1


pthread_t dios;                 // Instancia del Thread principal para la generacion de vehiculos
pthread_t thread_id[NUM_THREADS];
pthread_t bridges[4];           // Instancia de cada uno de los Threads de puentes

*/


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
/*

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
            TCB carro = (TCB) malloc(sizeof(struct thread_data));
            carro -> thread_id=i;
            carro -> bridge = i;
            carro -> scheduler=RR;
            carro -> next = NULL;

            if(tipo_carro == CARRO)
            {
                carro->type = RADIOACTIVO;
            }
            else if(tipo_carro == RADIOACTIVO)
            {
                carro->type = CARRO;
            }
            else
            {
                carro->type = AMBULANCIA;
            }

            add_node(carro,carros);
            pthread_create(&thread_id[i], NULL, scheduling, (void *) carro);

            TCB carro_puente = (TCB) malloc(sizeof(struct thread_data));
            carro_puente -> thread_id=i;
            carro_puente -> bridge = i;
            carro_puente -> scheduler=RR;
            carro_puente -> next = NULL;

            if(tipo_carro == CARRO)
            {
                carro_puente->type = RADIOACTIVO;
            }
            else if(tipo_carro == RADIOACTIVO)
            {
                carro_puente->type = CARRO;
            }
            else
            {
                carro_puente->type = AMBULANCIA;
            }


            add_node(carro_puente,puente_1_izq);
            printf("Generando carro de tipo %d al lado %d del puente %d \n",tipo_carro, lado_puente, i);

        }
        else
        {

            int tipo_carro = numero_random_tipo();
            TCB carro = (TCB) malloc(sizeof(struct thread_data));
            carro -> thread_id=i;
            carro -> bridge = i;
            carro -> scheduler=RR;
            carro -> next = NULL;

            if(tipo_carro == CARRO)
            {
                carro->type = RADIOACTIVO;
            }
            else if(tipo_carro == RADIOACTIVO)
            {
                carro->type = CARRO;
            }
            else
            {
                carro->type = AMBULANCIA;
            }

            add_node(carro,carros);
            pthread_create(&thread_id[i], NULL, scheduling, (void *) carro);


            TCB carro_puente = (TCB) malloc(sizeof(struct thread_data));
            carro_puente -> thread_id=i;
            carro_puente -> bridge = i;
            carro_puente -> scheduler=RR;
            carro_puente -> next = NULL;

            if(tipo_carro == CARRO)
            {
                carro_puente->type = RADIOACTIVO;
            }
            else if(tipo_carro == RADIOACTIVO)
            {
                carro_puente->type = CARRO;
            }
            else
            {
                carro_puente->type = AMBULANCIA;
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
}*/

// Se encarga de generar periodicamente para cada puente carros
// estos carros van a pertenecer a uno de los lados del puente para el que se genera
void *algoritmo_puentes(void *t)
{

    while(1)
    {
        //  printf("Algoritmo puente \n");
        sleep(3);
    }

}

int main()
{

    Bridge puente_0_data  = (Bridge) malloc(sizeof(struct bridges));
    puente_0_data -> bridge_id = 0;
    puente_0_data -> current_cars = malloc(sizeof(struct thread_list));
    puente_0_data -> occupancy = 0;
    puente_0_data -> capacity = 4;
    puente_0_data -> control = OFICIAL;
    puente_0_data -> k = 9;
    puente_0_data -> coming_out = 0;

    pthread_t dios;
    mythread_create(&dios, NULL, algoritmo_puentes, (void *) puente_0_data, 0, 0, 0,0);

    /* carros = malloc(sizeof(struct thread_list));
     puente_1_der = malloc(sizeof(struct thread_list));
     puente_1_izq = malloc(sizeof(struct thread_list));

     Bridge puente_0_data  = (Bridge) malloc(sizeof(struct bridges));
     puente_0_data -> bridge_id = 0;
     puente_0_data -> current_cars = malloc(sizeof(struct thread_list));
     puente_0_data -> occupancy = 0;
     puente_0_data -> capacity = 4;
     puente_0_data -> control = OFICIAL;
     puente_0_data -> k = 9;
     puente_0_data -> coming_out = 0;


     int th = pthread_create(&dios, NULL, generador_carros, (void *) dios);
     if ( th )
     {
         printf("Error creando el hilo principal \n");
     }




     th = pthread_create(&bridges[0], NULL, algoritmo_puentes, (void *) puente_0_data);
     if ( th )
     {
         printf("Error creando el puente 1 \n");
     }

     pthread_join(dios,NULL);
     pthread_join(bridges[0], NULL);

     free_mem(carros);
     free_mem(puente_1_izq);
     free_mem(puente_1_der);

     free(carros);
     free(puente_1_izq);
     free(puente_1_der);
    */
    return 0;

}

