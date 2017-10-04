#include "manejo_carros.h"
#include "algoritmos_control.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

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

                if(puente_tmp->carros_circulando->head->thread_identificador == data->thread_identificador)    // Si no hay carros al frente
                {
                    if(distancia_tmp == puente_tmp->capacidad)          // Ya termino de correrse todos los espacios disponibles
                    {

                        pthread_mutex_lock(&lock_thread_terminado);

                        printf(ANSI_COLOR_YELLOW "Carro %d termino de pasar el puente, no habia alguien en frente %d\n" ANSI_COLOR_RESET, data->thread_identificador, puente_tmp->carros_circulando->tamanio);
                        //eliminar_nodo_carro(carros_ui,data->thread_identificador);
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
                        /* printf("Carro %lu moviendose %d \n", data->thread_identificador, distancia_tmp);
                        usleep(data->velocidad*100000);                                              // Simulo la velocidad
                        distancia_tmp ++;                                                   // Auento la distancia recorrida
                        */

                        if(hardware == 1 && data->puente<3)
                        {
                            principal(data->puente,data->lado_izquierdo,0,0,1,distancia_tmp,1,data->tipo_carro);
                            printf("Carro %lu moviendose %d\n", data->thread_identificador, distancia_tmp, data->lado_izquierdo);
                            usleep(data->velocidad*100000);                                             // Simulo la velocidad
                            //sleep(1);
                            principal(data->puente,data->lado_izquierdo,0,0,1,distancia_tmp,0,data->tipo_carro);
                            //sleep(1);
                            distancia_tmp ++;
                        }
                        else
                        {

                            printf("Carro %lu moviendose %d\n", data->thread_identificador, distancia_tmp, data->lado_izquierdo);
                            usleep(data->velocidad*100000);                                             // Simulo la velocidad
                            distancia_tmp ++;

                            if(data->lado_izquierdo == 1)
                            {
                                data->objeto.x += 100;
                            }
                            else if(data->lado_izquierdo == 0)
                            {
                                data->objeto.x -= 100;
                            }

                        }
                        // Auento la distancia recorrida

                    }
                }
                else                    // Hay un carro en frente
                {

                    if(distancia_tmp == puente_tmp->capacidad)          // Ya termino de correrse todos los espacios disponibles
                    {

                        pthread_mutex_lock(&lock_thread_terminado);

                        printf(ANSI_COLOR_YELLOW "Carro %d termino de pasar el puente, habia alguien en frente %d\n" ANSI_COLOR_RESET, data->thread_identificador, puente_tmp->carros_circulando->tamanio);

                        //eliminar_nodo_carro(carros_ui,data->thread_identificador);
                        eliminar_nodo_thread(threads,data->thread_identificador);           // Elimino el carro de la lista de hilos
                        eliminar_nodo_carro(buscar_nodo_thread(threads,data->puente)->puente->carros_circulando,data->thread_identificador);    // Elimino el carro de la lista de los carros circulando de su debido puente
                        buscar_nodo_thread(threads,data->puente)->puente->ocupancia -= 1;


                        thread_terminado = 1;
                        pthread_mutex_unlock(&lock_thread_terminado);


                        pthread_t id = pthread_self();
                        pthread_detach(id);
                        return 0;

                    }
                    else
                    {
                        /*printf("Carro %lu moviendose %d \n", data->thread_identificador, distancia_tmp);
                        usleep(buscar_nodo_carro(puente_tmp->carros_circulando,data->thread_identificador)->prev->velocidad*100000);                                             // Utilizo la velocidad del nodo del frente
                        distancia_tmp ++;         */                               // Aumento la distancia avanzada

                        if(hardware == 1 && data->puente<3)
                        {

                            principal(data->puente,data->lado_izquierdo,0,0,1,distancia_tmp,1,data->tipo_carro);
                            printf("Carro %lu moviendose %d\n", data->thread_identificador, distancia_tmp);
                            //sleep(1);
                            usleep(buscar_nodo_carro(puente_tmp->carros_circulando,data->thread_identificador)->prev->velocidad*100000);
                            principal(data->puente,data->lado_izquierdo,0,0,1,distancia_tmp,0,data->tipo_carro);
                            //sleep(1);
                            distancia_tmp ++;
                        }
                        else
                        {
                            printf("Carro %lu moviendose %d\n", data->thread_identificador, distancia_tmp);
                            usleep(buscar_nodo_carro(puente_tmp->carros_circulando,data->thread_identificador)->prev->velocidad*100000);
                            distancia_tmp ++;


                            if(data->lado_izquierdo == 1)
                            {
                                data->objeto.x += 100;
                            }
                            else if(data->lado_izquierdo == 0)
                            {
                                data->objeto.x -= 100;
                            }

                        }
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

       // usleep(10000);
    }
}




// Utiliza la lista global de los hilos para encontrar el puente en el que tiene que insertar carros
void *generador_carros(void *t)
{
    int i = 4;
    //pthread_t array [10000];
    double lambda = 0.5;
    double probabilidad = 0.0;
    double porcentaje_ambulancia = 0.0;
    while(i < 15)
    {
        srand(time(NULL));
        //printf("Generando carro %lu de tipo %d al lado %d del puente %d \n",i, carro->tipo_carro, lado_random, puente_random);

        int puente_random = rand() % 3;
        int lado_random = rand() % 2;

        Thread_Carro carro = (Thread_Carro) calloc(1, sizeof(struct thread_carro));
        carro -> thread_identificador = i;
        carro -> corriendo = 0;
        carro -> puente = puente_random;
        carro -> pintado = 0;
        if(gui == 1)
        {
            carro -> velocidad = rand()%30;

        }
        else if(hardware == 1)
        {
            carro -> velocidad = rand()%3;
        }
        else
        {
            carro -> velocidad = rand() / (RAND_MAX + 1.);
        }


        switch (puente_random)
        {
        case 0:
            probabilidad = lambda*pow(2.71828,-lambda*getParameterValueConfigDouble("config_puente_0.txt","distribucion_exponencial"));
            porcentaje_ambulancia = getParameterValueConfigDouble("config_puente_0.txt","probabilidad_ambulancia");
            break;
        case 1:
            probabilidad = lambda*pow(2.71828,-lambda*getParameterValueConfigDouble("config_puente_1.txt","distribucion_exponencial"));
            porcentaje_ambulancia = getParameterValueConfigDouble("config_puente_1.txt","probabilidad_ambulancia");
            break;
        case 2:
            probabilidad = lambda*pow(2.71828,-lambda*getParameterValueConfigDouble("config_puente_2.txt","distribucion_exponencial"));
            porcentaje_ambulancia = getParameterValueConfigDouble("config_puente_2.txt","probabilidad_ambulancia");
            break;
        case 3:
            probabilidad = lambda*pow(2.71828,-lambda*getParameterValueConfigDouble("config_puente_3.txt","distribucion_exponencial"));
            porcentaje_ambulancia = getParameterValueConfigDouble("config_puente_3.txt","probabilidad_ambulancia");
            break;
        }



        if(rand() < probabilidad *( (double) RAND_MAX) )
        {
            carro -> tipo_carro = RADIOACTIVO;
            carro -> prioridad = 0;
            carro -> vida_carro = rand() % 10;
            carro -> limite_tiempo = rand() % 20;
        }

        else
        {
            if(rand()%100 < porcentaje_ambulancia*100)
            {
                carro -> tipo_carro = AMBULANCIA;
                carro -> prioridad = 1;
                carro -> vida_carro =(int) rand % 60;
                carro -> limite_tiempo =(int) rand % 80;
            }
            else
            {
                carro -> tipo_carro = CARRO;
                carro -> prioridad = 2;
                carro -> vida_carro = 1000;
                carro -> limite_tiempo = 1000;
            }
        }


        pthread_t carro_thread;
        if(lado_random == 0)        // Izquierda
        {
            carro->lado_izquierdo = 1;
            if(puentes->tamanio > 0 && buscar_nodo_puente(puentes,puente_random) != NULL)
            {
                agregar_carro_prioridad(carro, buscar_nodo_puente(puentes,puente_random)->carros_izquierda);

            }
            else
            {
                agregar_carro_prioridad(carro, buscar_nodo_thread(threads,puente_random)->puente->carros_izquierda);
                //printf("prev %p \n",buscar_nodo_thread(threads,puente_random)->puente->carros_izquierda->head->prev);
            }

        }
        else        // Derecha
        {
            carro->lado_izquierdo = 0;
            if(puentes->tamanio > 0 && buscar_nodo_puente(puentes,puente_random) != NULL)
            {
                agregar_carro_prioridad(carro, buscar_nodo_puente(puentes,puente_random)->carros_derecha);
            }
            else
            {
                agregar_carro_prioridad(carro, buscar_nodo_thread(threads,puente_random)->puente->carros_derecha);
            }

        }


        if(gui == 1)        // Se debe inicializar la textura del carro
        {

            if(carro->lado_izquierdo == 1)
            {

                carro->objeto.x = 0; //Extreme left of the window
            }
            else
            {
                carro->objeto.x = SCREEN_WIDTH - 38; //Extreme left of the window
            }

            // Valida si el tipo de carro es ambulacia o radioactivo para disminuir la cantidad de la lista
            switch(puente_random)
            {
            case 0:
                carro->objeto.y = 165; //Very bottom of the window
                break;
            case 1:

                carro->objeto.y = 298; //Very bottom of the window
                break;

            case 2:
                carro->objeto.y = 435; //Very bottom of the window
                break;

            case 3:
                carro->objeto.y = 580; //Very bottom of the window
                break;
            }

        }



        Thread thread_nuevo = (Thread) calloc(1, sizeof(struct thread));
        thread_nuevo->puente=NULL;
        thread_nuevo->carro=carro;
        thread_nuevo->prioridad = carro->prioridad;
        thread_nuevo->velocidad = carro->velocidad;
        thread_nuevo->calendarizador=calendarizador;
        thread_nuevo->thread_identificador=i;

        if(calendarizador == 3)             // Si se esta trabajando con Priority Queue
        {
            agregar_thread_prioridad(thread_nuevo, threads);
        }
        else if(calendarizador == 2)
        {
            agregar_thread_velocidad(thread_nuevo, threads);
        }
        else if (calendarizador == 4)
        {
            agregar_thread_Tiempo_Real(thread_nuevo,threads);

        }
        else
        {
            agregar_thread(thread_nuevo,threads);
        }



        if(puentes->tamanio > 0 && buscar_nodo_puente(puentes,puente_random) != NULL)
        {
            pthread_create(&carro_thread, NULL, controlador_carros_jungla, (void *) carro);
        }
        else
        {
            pthread_create(&carro_thread, NULL, controlador_carros, (void *) carro);
        }

        //pthread_join(carro_thread, NULL);

        //usleep(60000);//usleep(600000); para regular          usleep(1000000); para semaforo
        sleep(1);
        i++;
    }
}

