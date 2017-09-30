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

typedef struct thread_espera
{
    //long thread_identificador_espera;
    int puente_identificador;
    int espera;

} *Thread_Espera;



typedef struct thread_carro
{
    long thread_identificador;             // Id para mantener referencia a los hilos

	// Para los carros
	int tipo_carro;                   // Tipo de carro
	int limite_tiempo;                  // Tiempo de vida
	int corriendo;                  // Para saber si puede avanzar
	int vida_carro;             // Vida antes de explotar (radioactivos)
	int puente;                 // Puente al que pertenece
	double velocidad;              // Velocidad del carro
	int lado_izquierdo;         // Para saber de cual lado es si lado_izquierdo = 1, el carro fue insertado del lado izq si es 0 fue del derecho
    int prioridad;

	struct thread_carro *next;
	struct thread_carro *prev;

	//pthread_t hilo;
} *Thread_Carro;



typedef struct thread_list_carro
{
	Thread_Carro head;
	Thread_Carro tail;
	int cantidad_radioactivos;
	int cantidad_ambulancias;
	int tamanio;
} *ThreadListCarro;


typedef struct thread_puente
{
    long thread_identificador;             // Id para mantener referencia a los hilos

	// Para el metodo del trafico
    int k;                      // Valor k de cantidad de carros que puede dejar pasar el transito

    // Para el metodo del semaforo
    int semaforo_izquierda;     // Semaforo del lado izquierdo 1 ON, 0 OFF
    int semaforo_derecha;       // Semaforo del lado derecho 1 ON, 0 OFF
    int tiempo_semaforo_izquierda;         // Tiempo que pasara el tsemaforo en cada estado 1 ON, 0 OFF
    int tiempo_semaforo_derecha; // Tiempo que pasara el semaforo en cada estado 1 ON, 0 OFF

    // Para todos los metodos
    int puente_id;              //identificador del puente
    int ocupancia;              // Cantidad de carros en el puente
    int capacidad;              // Capacidad del puente
    int control;                // Metodo de control, deberia ser redundante
    ThreadListCarro carros_circulando;          // Lista de carros que estan circulando, se utiliza para que los carros sepan quien esta adelante y atras
    ThreadListCarro carros_izquierda;    // Lista de carros en el lado izquierdo
	ThreadListCarro carros_derecha;      // Lista de carros en el lado derecho

	int temporizando;       // Se utiliza para identificar si el puente esta esperando dejar de ser temporizado
	int temporizado_parcial;


	struct thread_puente *next;
	struct thread_puente *prev;

   // pthread_t hilo;
} *Thread_Puente;


typedef struct thread_list_puente
{
	Thread_Puente head;
	Thread_Puente tail;
	int tamanio;
} *ThreadListPuente;



typedef struct thread
{
    Thread_Carro carro;
    Thread_Puente puente;
	long thread_identificador;             // Id para mantener referencia a los hilos
    long calendarizador;              // Tipo de calendarizador en uso


    struct thread *next;
    struct thread *prev;
} *Thread;

typedef struct thread_list
{
	Thread head;
	Thread tail;
	int tamanio;
} *ThreadList;


void agregar_puente(Thread_Puente node, ThreadListPuente list);
void agregar_carro(Thread_Carro node, ThreadListCarro list);
void agregar_thread(Thread node, ThreadList list);
void agregar_thread_priority(Thread_Carro node, ThreadList list);

Thread_Carro pop_primer_thread_carro(ThreadListCarro list);
Thread pop_primer_thread(ThreadList list);

Thread buscar_nodo_thread(ThreadList list, long thread_identificador);
Thread_Carro buscar_nodo_carro(ThreadListCarro list, long thread_identificador);
Thread_Puente buscar_nodo_puente(ThreadListPuente list, long thread_identificador);

void eliminar_nodo_carro(ThreadListCarro list, long thread_identificador);
void eliminar_nodo_thread(ThreadList list, long thread_identificador);


#endif
