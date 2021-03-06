#include "algoritmos_control.h"
#include "rasp.h"

/*
* Algoritmo para el metodo de control del transito
*/
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
                    printf(ANSI_COLOR_RED "Trafico termino" ANSI_COLOR_RESET);
                    printf(" de dejar pasar sus carros del lado izquierdo\n");
                    //temporal_k_izquierda = 0;
                    thread_terminado = 1;
                    pthread_mutex_unlock(&lock_thread_terminado);
                    break;

                }

                if (data->ocupancia == data->capacidad)         // Puente lleno
                {
                    printf(ANSI_COLOR_RED "Puente lleno," ANSI_COLOR_RESET);
                    printf(" haciendo esperar a los carros de la izquierda  \n");
                    pthread_mutex_lock(&lock_thread_terminado);
                    thread_terminado = 1;
                    pthread_mutex_unlock(&lock_thread_terminado);

                    break;
                }
                else                                            // Puente con campo
                {
                    if((data->carros_izquierda->tamanio > 0) && (data->ocupancia < data->capacidad))
                    {
                        if(data->carros_circulando->tamanio > 0 && data->carros_circulando->head->lado_izquierdo == 0)  // Se niega el acceso, es preventivo
                        {
                            printf(ANSI_COLOR_RED "Puente yendo en direccion contraria para insertar\n" ANSI_COLOR_RESET);

                            pthread_mutex_lock(&lock_thread_terminado);
                            thread_terminado = 1;
                            pthread_mutex_unlock(&lock_thread_terminado);

                            break;

                        }

                        Thread_Carro tmp = pop_primer_thread_carro(data->carros_izquierda); // Extraigo la cabeza de la lista del lado izquierdo y reordeno
                        agregar_carro(tmp,data->carros_circulando);     // Paso el thread a los que estan circulando

                        pthread_mutex_lock(&lock_contador_tmp);
                        buscar_nodo_thread(threads,tmp->thread_identificador)->carro->corriendo = 1; // Poner a caminar el carro

                        if(tmp->tipo_carro == RADIOACTIVO)
                        {
                            printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                        }
                        else if(tmp->tipo_carro == AMBULANCIA)
                        {
                            printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                        }
                        else
                        {
                            printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                        }

                        data->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad
                        temporal_k_izquierda += 1;
                        pthread_mutex_unlock(&lock_contador_tmp);

                    }
                    else
                    {
                        pthread_mutex_lock(&lock_thread_terminado);
                        printf(ANSI_COLOR_RED "No hay carros" ANSI_COLOR_RESET);
                        printf(" a la izquierda del puente \n");
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
                        printf(ANSI_COLOR_RED "Trafico termino" ANSI_COLOR_RESET);
                        printf(" de dejar pasar sus carros del lado derecho\n");
                        temporal_k_derecha = 0;             // Reinicio temporal
                        temporal_k_izquierda = 0;           // Reinicio temporal
                        thread_terminado = 1;
                        pthread_mutex_unlock(&lock_thread_terminado);
                        break;

                    }

                    if (data->ocupancia == data->capacidad)         // Puente lleno
                    {
                        printf(ANSI_COLOR_RED "Puente lleno," ANSI_COLOR_RESET);
                        printf(" haciendo esperar a los carros de la derecha  \n");
                        pthread_mutex_lock(&lock_thread_terminado);
                        thread_terminado = 1;
                        pthread_mutex_unlock(&lock_thread_terminado);

                        break;
                    }
                    else                                            // Puente con campo
                    {
                        if((data->carros_derecha->tamanio > 0) && (data->ocupancia < data->capacidad))
                        {





                            if(data->carros_circulando->tamanio > 0 && data->carros_circulando->head->lado_izquierdo == 1)  // Se niega el acceso, es preventivo
                            {
                                printf(ANSI_COLOR_RED "Puente yendo en direccion contraria para insertar\n" ANSI_COLOR_RESET);

                                pthread_mutex_lock(&lock_thread_terminado);
                                thread_terminado = 1;
                                pthread_mutex_unlock(&lock_thread_terminado);

                                break;

                            }




                            Thread_Carro tmp = pop_primer_thread_carro(data->carros_derecha); // Extraigo la cabeza de la lista del lado izquierdo y reordeno
                            agregar_carro(tmp,data->carros_circulando);     // Paso el thread a los que estan circulando

                            pthread_mutex_lock(&lock_contador_tmp);
                            buscar_nodo_thread(threads,tmp->thread_identificador)->carro->corriendo = 1; // Poner a caminar el carro


                            if(tmp->tipo_carro == RADIOACTIVO)
                            {
                                printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                            }
                            else if(tmp->tipo_carro == AMBULANCIA)
                            {
                                printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                            }
                            else
                            {
                                printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                            }


                            data->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad
                            temporal_k_derecha += 1;
                            pthread_mutex_unlock(&lock_contador_tmp);

                        }
                        else
                        {
                            pthread_mutex_lock(&lock_thread_terminado);
                            printf(ANSI_COLOR_RED "No hay carros" ANSI_COLOR_RESET);
                            printf(" a la derecha del puente \n");
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
        usleep(100000);
    }
}


/*
* Algoritmo para el metodo de control del semaforo
*/
void *algoritmo_puente_semaforo(void *puente)
{
    Thread_Puente data = (Thread_Puente) puente;
    int espera_tmp =0;

    while(1)
    {
        if(thread_actual == data->thread_identificador && thread_terminado == 0)
        {

            if(data->carros_circulando->head != NULL)
            {
                if(((data->carros_circulando->head->lado_izquierdo == 0) && (data->semaforo_izquierda == 1)) ||
                        ((data->carros_circulando->head->lado_izquierdo == 1) && (data->semaforo_izquierda == 0)))
                {
                    printf(ANSI_COLOR_YELLOW "Espera Amarillo en PUENTE %lu\n" ANSI_COLOR_RESET, data->thread_identificador);
                    pthread_mutex_lock(&lock_thread_terminado);
                    thread_terminado = 1;
                    pthread_mutex_unlock(&lock_thread_terminado);
                }
            }


            if(data->semaforo_izquierda == 1)        // el izquierdo esta encendido en verde
            {

            if(hardware == 1 && data->thread_identificador > 3){
                    semaforo(data->thread_identificador,1,1);
                    semaforo(data->thread_identificador,0,0);
                    //semaforo(data->thread_identificador,1,1);
                }

                data->temporizando = 1;     // Se auto indica que esta esperando
                espera_tmp = data->temporizado_parcial;

                while(espera_tmp <= data->tiempo_semaforo_izquierda && thread_actual == data->thread_identificador && thread_terminado == 0)          // Mientras no se dispare el temporizador
                {
                    if(thread_actual == data->thread_identificador && thread_terminado == 0)
                    {
                        if(espera_tmp == data->tiempo_semaforo_izquierda)
                        {
                            data->temporizando = 0;
                            break;
                        }
                        while(data->carros_izquierda->tamanio > 0 && data->carros_circulando->tamanio < data->capacidad)
                        {
                            if(thread_actual == data->thread_identificador && thread_terminado == 0)
                            {
                                Thread_Carro tmp = pop_primer_thread_carro(data->carros_izquierda); // Extraigo la cabeza de la lista del lado izquierdo y reordeno
                                agregar_carro(tmp,data->carros_circulando);     // Paso el thread a los que estan circulando
                                if(tmp->tipo_carro == RADIOACTIVO)
                                {
                                    printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                                }
                                else if(tmp->tipo_carro == AMBULANCIA)
                                {
                                    printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                                }
                                else
                                {
                                    printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                                };

                                buscar_nodo_thread(threads,tmp->thread_identificador)->carro->corriendo = 1; // Poner a caminar el carro
                                data->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad
                            }
                            else
                            {
                                data->temporizado_parcial = espera_tmp;
                                pthread_mutex_lock(&lock_thread_terminado);
                                thread_terminado = 1;
                                pthread_mutex_unlock(&lock_thread_terminado);
                                break;
                            }

                        }
                        espera_tmp += 1;

                    }
                    else
                    {
                        data->temporizado_parcial = espera_tmp;
                        pthread_mutex_lock(&lock_thread_terminado);
                        thread_terminado = 1;

                        pthread_mutex_unlock(&lock_thread_terminado);
                        break;
                    }

                }

                espera_tmp = 0;
                //printf("Sali \n");
                printf("Cambio semaforo izquierda a");
                printf(ANSI_COLOR_RED " rojo" ANSI_COLOR_RESET);
                printf(" y derecho a");
                printf(ANSI_COLOR_GREEN " verde" ANSI_COLOR_RESET);
                printf(" en PUENTE %d \n", data->puente_id);



                if(hardware == 1 && data->thread_identificador > 3){
                    //semaforo(data->thread_identificador,0,0);

                    semaforo(data->thread_identificador,1,0);
                   semaforo(data->thread_identificador,0,1);
                }


                data->semaforo_izquierda = 0; //izquierda a rojo
                //pthread_mutex_unlock(&lock_comenzar_espera);
            }

            if(data->semaforo_izquierda == 0)
            {

                if(hardware == 1){
                    semaforo(data->thread_identificador,0,1);
                    semaforo(data->thread_identificador,1,0);
                    //semaforo(data->thread_identificador,1,0);
                }

                //pthread_mutex_lock(&lock_comenzar_espera);
                data->temporizando = 1;     // Se auto indica que esta esperando
                espera_tmp = data->temporizado_parcial;

                while(espera_tmp <= data->tiempo_semaforo_derecha && thread_actual == data->thread_identificador && thread_terminado == 0)          // Mientras no se dispare el temporizador
                {
                    if(thread_actual == data->thread_identificador && thread_terminado == 0)
                    {
                        if(espera_tmp == data->tiempo_semaforo_derecha)
                        {
                            data->temporizando = 0;
                            break;
                        }
                        while(data->carros_derecha->tamanio > 0 && data->carros_circulando->tamanio < data->capacidad)
                        {
                            if(thread_actual == data->thread_identificador && thread_terminado == 0)
                            {
                                Thread_Carro tmp = pop_primer_thread_carro(data->carros_derecha); // Extraigo la cabeza de la lista del lado izquierdo y reordeno
                                agregar_carro(tmp,data->carros_circulando);     // Paso el thread a los que estan circulando

                                if(tmp->tipo_carro == RADIOACTIVO)
                                {
                                    printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                                }
                                else if(tmp->tipo_carro == AMBULANCIA)
                                {
                                    printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                                }
                                else
                                {
                                    printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %lu\n" ANSI_COLOR_RESET, tmp->thread_identificador, data->thread_identificador);
                                }

                                buscar_nodo_thread(threads,tmp->thread_identificador)->carro->corriendo = 1; // Poner a caminar el carro
                                data->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad

                            }
                            else
                            {
                                data->temporizado_parcial = espera_tmp;
                                pthread_mutex_lock(&lock_thread_terminado);
                                thread_terminado = 1;
                                pthread_mutex_unlock(&lock_thread_terminado);
                                break;


                            }

                        }

                        //usleep(1000000);
                        espera_tmp += 1;

                    }
                    else
                    {
                        data->temporizado_parcial = espera_tmp;
                        pthread_mutex_lock(&lock_thread_terminado);
                        thread_terminado = 1;
                        pthread_mutex_unlock(&lock_thread_terminado);
                        break;

                    }

                }

                espera_tmp = 0;
                //printf("Sali \n");

                printf("Cambio semaforo derecha a");
                printf(ANSI_COLOR_RED " rojo" ANSI_COLOR_RESET);
                printf(" y izquierdo a");
                printf(ANSI_COLOR_GREEN " verde" ANSI_COLOR_RESET);
                printf(" en PUENTE %d \n", data->puente_id);

                if(hardware == 1){
                    //semaforo(data->thread_identificador,0,1);

                    semaforo(data->thread_identificador,0,0);
                    semaforo(data->thread_identificador,1,1);
                }

                data->semaforo_izquierda = 1; //izquierda a rojo
                //pthread_mutex_unlock(&lock_comenzar_espera);

                pthread_mutex_lock(&lock_thread_terminado);
                thread_terminado = 1;
                pthread_mutex_unlock(&lock_thread_terminado);


            }


        }
        //usleep(100000);
    }
}



/*
* Algoritmo para el metodo de control de la jungla
*/
void *controlador_carros_jungla(void *carro)
{
    Thread_Carro data = (Thread_Carro) carro;

    int distancia_tmp = 0;
    long id = data->thread_identificador;
    int corriendo = data->corriendo;
    int puente = data->puente;
    int velocidad_tmp = 0;
    while(1)
    {
        if(thread_actual == id && thread_terminado == 0)
        {
            if(corriendo == 0)
            {
                Thread_Puente puente_temporal = buscar_nodo_puente(puentes,puente);
                if(puente_temporal->carros_circulando->tamanio < puente_temporal->capacidad)  // Hay espacio para pasar
                {
                    if(data->lado_izquierdo == 1)           // Estoy en el lado izquierdo del puente
                    {
                        if(puente_temporal->carros_circulando->head == NULL)
                        {
                            eliminar_nodo_carro(puente_temporal->carros_izquierda, id);
                            agregar_carro(data,puente_temporal->carros_circulando);     // Paso el thread a los que estan circulando


                            if(data->tipo_carro == RADIOACTIVO)
                            {
                                printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %d\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else if(data->tipo_carro == AMBULANCIA)
                            {
                                printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %d\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else
                            {
                                printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %d\n" ANSI_COLOR_RESET, id, puente);
                            }

                            data->vida_carro -= 1;
                            corriendo = 1; // Poner a caminar el carro
                            puente_temporal->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad
                        }
                        else if(puente_temporal->carros_circulando->head->lado_izquierdo == 1 && (int)puente_temporal->carros_circulando < (int)puente_temporal->capacidad)
                        {

                            agregar_carro(data,puente_temporal->carros_circulando);     // Paso el thread a los que estan circulando
                            eliminar_nodo_carro(puente_temporal->carros_izquierda, id);

                            if(data->tipo_carro == RADIOACTIVO)
                            {
                                printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %d\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else if(data->tipo_carro == AMBULANCIA)
                            {
                                printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %d\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else
                            {
                                printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %d\n" ANSI_COLOR_RESET, id, puente);
                            }
                            data->vida_carro -= 1;
                            corriendo = 1; // Poner a caminar el carro
                            puente_temporal->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es s
                        }
                        else
                        {
                            printf("No pude entrar, viene gente del otro lado\n");
                            pthread_mutex_lock(&lock_thread_terminado);
                            data->vida_carro -= 1;
                            thread_terminado = 1;
                            pthread_mutex_unlock(&lock_thread_terminado);
                        }

                    }
                    else
                    {
                        if(puente_temporal->carros_circulando->head == NULL)
                        {
                            eliminar_nodo_carro(puente_temporal->carros_derecha, id);
                            agregar_carro(data,puente_temporal->carros_circulando);     // Paso el thread a los que estan circulando


                            if(data->tipo_carro == RADIOACTIVO)
                            {
                                printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %d\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else if(data->tipo_carro == AMBULANCIA)
                            {
                                printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %d\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else
                            {
                                printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %d\n" ANSI_COLOR_RESET, id, puente);
                            }
                            data->vida_carro -= 1;
                            corriendo = 1; // Poner a caminar el carro
                            puente_temporal->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es su responsabilidad

                        }
                        else if(puente_temporal->carros_circulando->head->lado_izquierdo == 1 && puente_temporal->carros_circulando < puente_temporal->capacidad)
                        {
                            agregar_carro(data,puente_temporal->carros_circulando);     // Paso el thread a los que estan circulando
                            eliminar_nodo_carro(puente_temporal->carros_derecha, id);

                            if(data->tipo_carro == RADIOACTIVO)
                            {
                                printf(ANSI_COLOR_GREEN "Agregando carro RADIOACTIVO %lu a circulacion sobre puente %d\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else if(data->tipo_carro == AMBULANCIA)
                            {
                                printf(ANSI_COLOR_RED "Agregando carro AMBULANCIA %lu a circulacion sobre puente %d\n" ANSI_COLOR_RESET, id, puente);
                            }
                            else
                            {
                                printf(ANSI_COLOR_CYAN "Agregando carro REGULAR %lu a circulacion sobre puente %d\n" ANSI_COLOR_RESET, id, puente);
                            }

                            data->vida_carro -= 1;
                            corriendo = 1; // Poner a caminar el carro
                            puente_temporal->ocupancia +=  1;         // Solo se aumenta la ocupancia, que el carro salga del puente es s
                        }
                        else
                        {
                            printf("No pude entrar, viene gente del otro lado\n");

                            pthread_mutex_lock(&lock_thread_terminado);
                            data->vida_carro -= 1;
                            thread_terminado = 1;
                            pthread_mutex_unlock(&lock_thread_terminado);

                        }
                    }
                }

            }

            else if(corriendo == 1)
            {
                Thread_Puente puente_tmp = buscar_nodo_puente(puentes,data->puente);
                if(data->vida_carro == 0)       // El carro muere
                {
                    pthread_mutex_lock(&lock_thread_terminado);
                    eliminar_nodo_carro(buscar_nodo_puente(puentes,data->puente)->carros_circulando,id);    // Elimino el carro de la lista de los carros circulando de su debido puente
                    eliminar_nodo_thread(threads,id);           // Elimino el carro de la lista de hilos
                    buscar_nodo_puente(puentes,data->puente)->ocupancia -= 1;
                    distancia_tmp = 0;
                    //printf(ANSI_COLOR_YELLOW "Carro %lu termino de pasar el puente, no habia alguien en frente %d\n" ANSI_COLOR_RESET, id, puente_tmp->carros_circulando->tamanio);

                    printf("Carro");
                    if(data->tipo_carro == RADIOACTIVO)
                    {
                        printf(ANSI_COLOR_GREEN " Radioactivo" ANSI_COLOR_RESET);
                    }
                    else if(data->tipo_carro == AMBULANCIA)
                    {
                        printf(ANSI_COLOR_RED " Ambulancia" ANSI_COLOR_RESET);
                    }
                    else
                    {
                        printf(ANSI_COLOR_CYAN " Regular" ANSI_COLOR_RESET);
                    }
                    printf(" %lu", id);
                    printf(ANSI_COLOR_YELLOW " murio pasando el puente %lu.\n" ANSI_COLOR_RESET, puente_tmp->thread_identificador);



                    thread_terminado = 1;
                    pthread_mutex_unlock(&lock_thread_terminado);
                    pthread_t id = pthread_self();
                    pthread_detach(id);
                    break;
                }




                if(buscar_nodo_carro(puente_tmp->carros_circulando,id) != NULL )    // Si no hay carros al frente
                {
                    if(buscar_nodo_carro(puente_tmp->carros_circulando,id)->prev == NULL )
                    {

                        if(distancia_tmp == puente_tmp->capacidad)          // Ya termino de correrse todos los espacios disponibles
                        {

                            if(gui == 1)
                            {
                                if(data->lado_izquierdo == 1)
                                {
                                    int i = 0;
                                    while(i < 10)
                                    {
                                        data->objeto.x += 1;
                                        data->objeto.y += 2;
                                        usleep(10000);
                                        i++;
                                    }
                                    i = 0;
                                    while(i<200)
                                    {
                                        data->objeto.x += 1;

                                        usleep(10000);
                                        i++;
                                    }
                                }
                                else
                                {
                                    int i = 0;
                                    while(i < 10)
                                    {
                                        data->objeto.x -= 1;
                                        data->objeto.y += 2;
                                        usleep(10000);
                                        i++;
                                    }
                                    i = 0;
                                    while(i<200)
                                    {
                                        data->objeto.x -= 1;

                                        usleep(10000);
                                        i++;
                                    }

                                }

                            }

                            pthread_mutex_lock(&lock_thread_terminado);
                            eliminar_nodo_carro(buscar_nodo_puente(puentes,data->puente)->carros_circulando,id);    // Elimino el carro de la lista de los carros circulando de su debido puente
                            eliminar_nodo_thread(threads,id);           // Elimino el carro de la lista de hilos
                            buscar_nodo_puente(puentes,data->puente)->ocupancia -= 1;
                            distancia_tmp = 0;

                            printf("Carro");
                            if(data->tipo_carro == RADIOACTIVO)
                            {
                                printf(ANSI_COLOR_GREEN " Radioactivo" ANSI_COLOR_RESET);
                            }
                            else if(data->tipo_carro == AMBULANCIA)
                            {
                                printf(ANSI_COLOR_RED " Ambulancia" ANSI_COLOR_RESET);
                            }
                            else
                            {
                                printf(ANSI_COLOR_CYAN " Regular" ANSI_COLOR_RESET);
                            }
                            printf(" %lu", id);
                            printf(ANSI_COLOR_YELLOW " termino de pasar el puente %lu, no habia nadie en frente.\n" ANSI_COLOR_RESET, puente_tmp->thread_identificador);



                            thread_terminado = 1;
                            pthread_mutex_unlock(&lock_thread_terminado);
                            pthread_t id = pthread_self();
                            pthread_detach(id);
                            break;
                        }
                        else
                        {

                            if(hardware == 1 && data->puente<3)
                            {
                                principal(puente,data->lado_izquierdo,0,0,1,distancia_tmp,1,data->tipo_carro);
                                printf("Carro");
                                if(data->tipo_carro == RADIOACTIVO)
                                {
                                    printf(ANSI_COLOR_GREEN " Radioactivo" ANSI_COLOR_RESET);
                                }
                                else if(data->tipo_carro == AMBULANCIA)
                                {
                                    printf(ANSI_COLOR_RED " Ambulancia" ANSI_COLOR_RESET);
                                }
                                else
                                {
                                    printf(ANSI_COLOR_CYAN " Regular" ANSI_COLOR_RESET);
                                }
                                printf(" %lu moiiiviendose sobre puente %d a velocidad %d, distancia: %d\n", id,puente,data->velocidad, distancia_tmp);


                                while(velocidad_tmp < data->velocidad)
                                {
                                    if(thread_actual != data->thread_identificador)     // Nos quitan el CPU
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        sleep(1);
                                        velocidad_tmp += 1;
                                    }

                                }

                                if(velocidad_tmp == data->velocidad)
                                {
                                    principal(puente,data->lado_izquierdo,0,0,1,distancia_tmp,0,data->tipo_carro);
                                    distancia_tmp ++;     // Aumento la distancia recorrida
                                    velocidad_tmp = 0;

                                }



                            }
                            else
                            {
                                printf("Carro");
                                if(data->tipo_carro == RADIOACTIVO)
                                {
                                    printf(ANSI_COLOR_GREEN " Radioactivo" ANSI_COLOR_RESET);
                                }
                                else if(data->tipo_carro == AMBULANCIA)
                                {
                                    printf(ANSI_COLOR_RED " Ambulancia" ANSI_COLOR_RESET);
                                }
                                else
                                {
                                    printf(ANSI_COLOR_CYAN " Regular" ANSI_COLOR_RESET);
                                }
                                printf(" %lu moviendose sobre puente %d a velocidad %d, distancia: %d\n", id,puente,data->velocidad, distancia_tmp);


                                if(data->lado_izquierdo == 1)
                                {
                                    if(distancia_tmp == 0)      // Primera posicion
                                    {
                                        int i = 0;
                                        while(i < 10)
                                        {
                                            data->objeto.x += 1;
                                            data->objeto.y += 2;
                                            usleep(40000);
                                            i ++;
                                        }
                                    }

                                    int i = 0;
                                    while(i < 115)
                                    {
                                        data->objeto.x += 1;
                                        usleep(10000);
                                        i ++;
                                    }
                                }
                                else if(data->lado_izquierdo == 0)
                                {

                                    if(distancia_tmp == 0)      // Primera posicion
                                    {
                                        int i = 0;
                                        while(i < 10)
                                        {
                                            data->objeto.x -= 1;
                                            data->objeto.y += 2;
                                            usleep(40000);
                                            i ++;
                                        }
                                    }

                                    int i = 115;
                                    while(i > 0)
                                    {
                                        data->objeto.x -= 1;
                                        usleep(10000);
                                        i --;

                                    }
                                }
                                sleep(data->velocidad);                                             // Simulo la velocidad
                                distancia_tmp ++;

                            }


                        }
                    }
                    else                      // Hay un carro en frente
                    {

                        if(distancia_tmp == puente_tmp->capacidad)          // Ya termino de correrse todos los espacios disponibles
                        {

                            if(gui == 1)
                            {
                                if(data->lado_izquierdo == 1)
                                {
                                    int i = 0;
                                    while(i < 10)
                                    {
                                        data->objeto.x += 1;
                                        data->objeto.y += 2;
                                        usleep(10000);
                                        i++;
                                    }
                                    i = 0;
                                    while(i<200)
                                    {
                                        data->objeto.x += 1;

                                        usleep(10000);
                                        i++;
                                    }
                                }
                                else
                                {
                                    int i = 0;
                                    while(i < 10)
                                    {
                                        data->objeto.x -= 1;
                                        data->objeto.y += 2;
                                        usleep(10000);
                                        i++;
                                    }
                                    i = 0;
                                    while(i<200)
                                    {
                                        data->objeto.x -= 1;

                                        usleep(10000);
                                        i++;
                                    }

                                }

                            }

                            pthread_mutex_lock(&lock_thread_terminado);
                            eliminar_nodo_carro( buscar_nodo_puente(puentes,data->puente)->carros_circulando,id);    // Elimino el carro de la lista de los carros circulando de su debido puente
                            eliminar_nodo_thread(threads,id);           // Elimino el carro de la lista de hilos
                            buscar_nodo_puente(puentes,data->puente)->ocupancia -= 1;


                            //printf(ANSI_COLOR_YELLOW "Carro %lu termino de pasar el puente, habia alguien en frente %d\n" ANSI_COLOR_RESET, id, puente_tmp->carros_circulando->tamanio);


                            printf("Carro");
                            if(data->tipo_carro == RADIOACTIVO)
                            {
                                printf(ANSI_COLOR_GREEN " Radioactivo" ANSI_COLOR_RESET);
                            }
                            else if(data->tipo_carro == AMBULANCIA)
                            {
                                printf(ANSI_COLOR_RED " Ambulancia" ANSI_COLOR_RESET);
                            }
                            else
                            {
                                printf(ANSI_COLOR_CYAN " Regular" ANSI_COLOR_RESET);
                            }
                            printf(" %lu", id);
                            printf(ANSI_COLOR_YELLOW " termino de pasar el puente %lu, habia alguien al frente.\n" ANSI_COLOR_RESET, puente_tmp->thread_identificador);




                            thread_terminado = 1;
                            pthread_mutex_unlock(&lock_thread_terminado);
                            pthread_t id = pthread_self();
                            pthread_detach(id);
                            break;
                            // return 0;

                        }
                        else
                        {
                            if(hardware == 1 && data->puente<3)
                            {
                                principal(puente,data->lado_izquierdo,0,0,1,distancia_tmp,1,data->tipo_carro);
                                printf("Carro");
                                if(data->tipo_carro == RADIOACTIVO)
                                {
                                    printf(ANSI_COLOR_GREEN " Radioactivo" ANSI_COLOR_RESET);
                                }
                                else if(data->tipo_carro == AMBULANCIA)
                                {
                                    printf(ANSI_COLOR_RED " Ambulancia" ANSI_COLOR_RESET);
                                }
                                else
                                {
                                    printf(ANSI_COLOR_CYAN " Regular" ANSI_COLOR_RESET);
                                }
                                printf(" %lu moviendose sobre puente %d a velocidad %d, distancia1: %d\n", id,puente,data->velocidad, distancia_tmp);


                                while(velocidad_tmp < buscar_nodo_carro(puente_tmp->carros_circulando,id)->prev->velocidad)
                                {
                                    if(thread_actual != data->thread_identificador)     // Nos quitan el CPU
                                    {
                                        break;
                                    }
                                    else
                                    {
                                        sleep(1);
                                        velocidad_tmp += 1;
                                    }

                                }

                                if(velocidad_tmp == data->velocidad)
                                {
                                    principal(puente,data->lado_izquierdo,0,0,1,distancia_tmp,0,data->tipo_carro);
                                    distancia_tmp ++;     // Aumento la distancia recorrida
                                    velocidad_tmp = 0;

                                }
                            }
                            else
                            {

                                printf("Carro");
                                if(data->tipo_carro == RADIOACTIVO)
                                {
                                    printf(ANSI_COLOR_GREEN " Radioactivo" ANSI_COLOR_RESET);
                                }
                                else if(data->tipo_carro == AMBULANCIA)
                                {
                                    printf(ANSI_COLOR_RED " Ambulancia" ANSI_COLOR_RESET);
                                }
                                else
                                {
                                    printf(ANSI_COLOR_CYAN " Regular" ANSI_COLOR_RESET);
                                }
                                printf(" %lu moviendose sobre puente %d a velocidad %d, distancia1: %d\n", id,puente,data->velocidad, distancia_tmp);


                                //sleep(buscar_nodo_carro(puente_tmp->carros_circulando,id)->prev->velocidad);
                                //distancia_tmp ++;


                                if(data->lado_izquierdo == 1)
                                {
                                    if(distancia_tmp == 0)      // Primera posicion
                                    {
                                        int i = 0;
                                        while(i < 10)
                                        {
                                            data->objeto.x += 1;
                                            data->objeto.y += 2;
                                            usleep(40000);
                                            i ++;
                                        }
                                    }

                                    int i = 0;
                                    while(i < 115)
                                    {
                                        data->objeto.x += 1;
                                        usleep(10000);
                                        i ++;
                                    }
                                }
                                else if(data->lado_izquierdo == 0)
                                {

                                    if(distancia_tmp == 0)      // Primera posicion
                                    {
                                        int i = 0;
                                        while(i < 10)
                                        {
                                            data->objeto.x -= 1;
                                            data->objeto.y += 2;
                                            usleep(40000);
                                            i ++;
                                        }
                                    }

                                    int i = 115;
                                    while(i > 0)
                                    {
                                        data->objeto.x -= 1;
                                        usleep(10000);
                                        i --;

                                    }
                                }
                                sleep(velocidad_tmp < buscar_nodo_carro(puente_tmp->carros_circulando,id)->prev->velocidad);                                             // Simulo la velocidad
                                distancia_tmp ++;





                            }
                            // Aumento la distancia avanzada
                        }

                    }

                }



            }
            else
            {

                printf("Undefined\n");
            }

            usleep(100000);

        }
    }


}
