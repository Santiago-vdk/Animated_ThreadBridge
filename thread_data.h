#ifndef _THREAD_DATA_H
#define _THREAD_DATA_H

#define RR		    0
#define FIFO	    1
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
// Cada nodo de la lista representa un nodo TCB con estos atributos
typedef struct thread_data
{
	long thread_id;             // Id para mantener referencia a los hilos
	int scheduler;              // Tipo de calendarizador en uso
	int type;                   // Tipo de carro
	int bridge;                 // Puente al que pertenece
	struct thread_data *next;

} *TCB;

typedef struct thread_list
{
	TCB head;
} *ThreadList;

// Estructura para cada uno de los puentes, el puente en general no el lado
// Deben existir 4, 1 por puente
typedef struct bridges
{
	int bridge_id;                  // Identificador del puente
	ThreadList current_cars;        // Lista de carros en el puente
	int occupancy;                  // Cantidad de carros en el puente
	int capacity;                   // Capacidad del puente
	int control;                    // Algoritmo de control, semaforo, oficial o JL
	int k;                          // Cantidad de carros que pueden pasar cuando el algoritmo es de oficial
	int tiempo_semaforo;            // Tiempo que se mantiene el semaforo en verde o en rojo
	int coming_out;
} *Bridge;

void add_node(TCB node, ThreadList list);
void print_list(ThreadList list);
void remove_node(int id, ThreadList list);
void free_mem(ThreadList list);
void copy_node(TCB src, TCB dst);

#endif
