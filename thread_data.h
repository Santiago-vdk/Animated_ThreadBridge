#include <pthread.h>

#ifndef _THREAD_DATA_H
#define _THREAD_DATA_H

#define RR		    0
#define FCFS	    1
#define SJF		    2
#define PQ          3   // Priority Queue
#define RT          4
#define CARRO	    0
#define AMBULANCIA	1
#define RADIOACTIVO	2
#define OFICIAL		0
#define SEMAFORO	1
#define JUNGLA		2
#define K		    10
#define NUM_THREADS 100
// Estructura general para cada objeto sea de tipo carro o un lado del puente
// Cada nodo de la lista representa un nodo Thread_Carro_Puente con estos atributos
typedef struct thread_data
{
	long thread_id;             // Id para mantener referencia a los hilos
	int calendarizador;              // Tipo de calendarizador en uso
	int tipo;                   // Tipo de carro
	int puente;                 // Puente al que pertenece
	int limite_tiempo;
	int corriendo;
	struct thread_data *next;
	pthread_t thread;


} *Thread_Carro_Puente;

typedef struct thread_list
{
	Thread_Carro_Puente head;
	int length;
} *ThreadList;



// Estructura para cada uno de los puentes, el puente en general no el lado
// Deben existir 4, 1 por puente
typedef struct puentes
{
	int bridge_id;                  // Identificador del puente
	ThreadList current_cars;        // Lista de carros en el puente
	int occupancy;                  // Cantidad de carros en el puente
	int capacity;                   // Capacidad del puente
	int control;                    // Algoritmo de control, semaforo, oficial o JL
	int k;                          // Cantidad de carros que pueden pasar cuando el algoritmo es de oficial
	int tiempo_semaforo;            // Tiempo que se mantiene el semaforo en verde o en rojo
	ThreadList carros_izq;
	ThreadList carros_der;
} *Puente;

void add_node(Thread_Carro_Puente node, ThreadList list);
Thread_Carro_Puente get_node(ThreadList list, int id);
void print_list(ThreadList list);
void remove_node(int id, ThreadList list);
void free_mem(ThreadList list);
void copy_node(Thread_Carro_Puente src, Thread_Carro_Puente dst);

#endif
