#include "puentes.h"
#include "lector_archivos.h"

Thread_Puente crear_puente_0()
{

    Thread_Puente puente_0 = (Thread_Puente) malloc(sizeof(struct thread_puente));

    puente_0 -> thread_identificador = 0;              // El id de los threads en los puentes es fijo
    puente_0 -> puente_id = 0;             // identificador del puente, para los puentes es el mismo que el id de thread
    puente_0 -> ocupancia = 0;             // Cantidad de carros que estan en el puente transitando

    puente_0 -> capacidad = 10;//getParameterValueConfig("config_puente_0.txt","capacidad");              // Capacidad, numero de carros en el puente al mismo tiempo
    puente_0 -> control = JUNGLA;           // Algoritmo de control del puente
    puente_0 -> k = 5;//getParameterValueConfig("config_puente_0.txt","k");

    puente_0 -> semaforo_izquierda = 1;
    puente_0 -> semaforo_derecha = 0;
    puente_0 -> tiempo_semaforo_izquierda = 1;
    puente_0 -> tiempo_semaforo_derecha = 1;


    puente_0 -> carros_circulando = malloc(sizeof(struct thread_list_carro));     // Contiene todos los threads de carros del puente
    puente_0 -> carros_circulando->tamanio = 0;
    puente_0 -> carros_circulando->cantidad_ambulancias = 0;
    puente_0 -> carros_circulando->cantidad_radioactivos = 0;

    puente_0 -> carros_izquierda = malloc(sizeof(struct thread_list_carro));
    puente_0 -> carros_izquierda -> tamanio = 0;
    puente_0 -> carros_izquierda->cantidad_ambulancias = 0;
    puente_0 -> carros_izquierda->cantidad_radioactivos = 0;

    puente_0 -> carros_derecha = malloc(sizeof(struct thread_list_carro));
    puente_0 -> carros_derecha -> tamanio = 0;
    puente_0 -> carros_derecha->cantidad_ambulancias = 0;
    puente_0 -> carros_derecha->cantidad_radioactivos = 0;

    puente_0 -> temporizando = 0;
    puente_0 -> temporizado_parcial = 0;      // Se utiliza para recordar cuanto tiempo se ha dejado pasar el semaforo

    return puente_0;
}


Thread_Puente crear_puente_1()
{
    Thread_Puente puente_1 = (Thread_Puente) malloc(sizeof(struct thread_puente));

    puente_1 -> thread_identificador = 1;              // El id de los threads en los puentes es fijo
    puente_1 -> puente_id = 1;             // identificador del puente, para los puentes es el mismo que el id de thread
    puente_1 -> ocupancia = 0;             // Cantidad de carros que estan en el puente transitando
    puente_1 -> capacidad =  10;              // Capacidad, numero de carros en el puente al mismo tiempo
    puente_1 -> control =JUNGLA;            // Algoritmo de control del puente
    puente_1 -> k =10;

    puente_1 -> semaforo_izquierda = 1;
    puente_1 -> semaforo_derecha = 0;
    puente_1 -> tiempo_semaforo_izquierda = 1;
    puente_1 -> tiempo_semaforo_derecha = 1;

    puente_1 -> carros_circulando = malloc(sizeof(struct thread_list_carro));     // Contiene todos los threads de carros del puente
    puente_1 -> carros_circulando->tamanio = 0;
    puente_1 -> carros_circulando->cantidad_ambulancias = 0;
    puente_1 -> carros_circulando->cantidad_radioactivos = 0;

    puente_1 -> carros_izquierda = malloc(sizeof(struct thread_list_carro));
    puente_1 -> carros_izquierda -> tamanio = 0;
    puente_1 -> carros_izquierda->cantidad_ambulancias = 0;
    puente_1 -> carros_izquierda->cantidad_radioactivos = 0;

    puente_1 -> carros_derecha = malloc(sizeof(struct thread_list_carro));
    puente_1 -> carros_derecha -> tamanio = 0;
    puente_1 -> carros_derecha->cantidad_ambulancias = 0;
    puente_1 -> carros_derecha->cantidad_radioactivos = 0;

    puente_1 -> temporizando = 0;
    puente_1 -> temporizado_parcial = 0;      // Se utiliza para recordar cuanto tiempo se ha dejado pasar el semaforo

    return puente_1;
}



Thread_Puente crear_puente_2()
{


    Thread_Puente puente_2 = (Thread_Puente) malloc(sizeof(struct thread_puente));

    puente_2 -> thread_identificador = 2;              // El id de los threads en los puentes es fijo
    puente_2 -> puente_id = 2;             // identificador del puente, para los puentes es el mismo que el id de thread
    puente_2 -> ocupancia = 0;             // Cantidad de carros que estan en el puente transitando
    puente_2 -> capacidad = 10;              // Capacidad, numero de carros en el puente al mismo tiempo
    puente_2 -> control = JUNGLA;            // Algoritmo de control del puente
    puente_2 -> k = 10;

    puente_2 -> semaforo_izquierda = 1;
    puente_2 -> semaforo_derecha = 0;
    puente_2 -> tiempo_semaforo_izquierda = 1;
    puente_2 -> tiempo_semaforo_derecha = 1;

    puente_2 -> carros_circulando = malloc(sizeof(struct thread_list_carro));     // Contiene todos los threads de carros del puente
    puente_2 -> carros_circulando->tamanio = 0;
    puente_2 -> carros_circulando->cantidad_ambulancias = 0;
    puente_2 -> carros_circulando->cantidad_radioactivos = 0;

    puente_2 -> carros_izquierda = malloc(sizeof(struct thread_list_carro));
    puente_2 -> carros_izquierda -> tamanio = 0;
    puente_2 -> carros_izquierda->cantidad_ambulancias = 0;
    puente_2 -> carros_izquierda->cantidad_radioactivos = 0;

    puente_2 -> carros_derecha = malloc(sizeof(struct thread_list_carro));
    puente_2 -> carros_derecha -> tamanio = 0;
    puente_2 -> carros_derecha->cantidad_ambulancias = 0;
    puente_2 -> carros_derecha->cantidad_radioactivos = 0;

    puente_2 -> temporizando = 0;
    puente_2 -> temporizado_parcial = 0;      // Se utiliza para recordar cuanto tiempo se ha dejado pasar el semaforo

    return puente_2;
}




Thread_Puente crear_puente_3()
{

    Thread_Puente puente_3 = (Thread_Puente) malloc(sizeof(struct thread_puente));

    puente_3 -> thread_identificador = 3;              // El id de los threads en los puentes es fijo
    puente_3 -> puente_id = 3;             // identificador del puente, para los puentes es el mismo que el id de thread
    puente_3 -> ocupancia = 0;             // Cantidad de carros que estan en el puente transitando
    puente_3 -> capacidad = 10;              // Capacidad, numero de carros en el puente al mismo tiempo
    puente_3 -> control = JUNGLA;            // Algoritmo de control del puente
    puente_3 -> k = 7;

    puente_3 -> semaforo_izquierda = 1;
    puente_3 -> semaforo_derecha = 0;
    puente_3 -> tiempo_semaforo_izquierda =1;
    puente_3 -> tiempo_semaforo_derecha = 1;

    puente_3 -> carros_circulando = malloc(sizeof(struct thread_list_carro));     // Contiene todos los threads de carros del puente
    puente_3 -> carros_circulando->tamanio = 0;
    puente_3 -> carros_circulando->cantidad_ambulancias = 0;
    puente_3 -> carros_circulando->cantidad_radioactivos = 0;

    puente_3 -> carros_izquierda = malloc(sizeof(struct thread_list_carro));
    puente_3 -> carros_izquierda -> tamanio = 0;
    puente_3 -> carros_izquierda->cantidad_ambulancias = 0;
    puente_3 -> carros_izquierda->cantidad_radioactivos = 0;

    puente_3 -> carros_derecha = malloc(sizeof(struct thread_list_carro));
    puente_3 -> carros_derecha -> tamanio = 0;
    puente_3 -> carros_derecha->cantidad_ambulancias = 0;
    puente_3 -> carros_derecha->cantidad_radioactivos = 0;

    puente_3 -> temporizando = 0;
    puente_3 -> temporizado_parcial = 0;      // Se utiliza para recordar cuanto tiempo se ha dejado pasar el semaforo

    return puente_3;
}


