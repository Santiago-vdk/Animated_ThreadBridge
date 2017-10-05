#include "manejo_carros.h"
#include "algoritmos_control.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

void *controlador_carros(void *carro)
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
                        printf(" %lu", data->thread_identificador);
                        printf(ANSI_COLOR_YELLOW " termino de pasar el puente %lu, no habia nadie en frente\n" ANSI_COLOR_RESET, puente_tmp->thread_identificador);

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



                        eliminar_nodo_thread(threads,data->thread_identificador);           // Elimino el carro de la lista de hilos
                        eliminar_nodo_carro(buscar_nodo_thread(threads,data->puente)->puente->carros_circulando,data->thread_identificador);    // Elimino el carro de la lista de los carros circulando de su debido puente
                        buscar_nodo_thread(threads,data->puente)->puente->ocupancia -= 1;

                        thread_terminado = 1;
                        distancia_tmp = 0;

                        pthread_mutex_unlock(&lock_thread_terminado);

                        pthread_t id = pthread_self();
                        pthread_detach(id);
                        //return 0;

                    }
                    else
                    {

                        if(hardware == 1 && data->puente<3)
                        {
                            principal(data->puente,data->lado_izquierdo,0,0,1,distancia_tmp,1,data->tipo_carro);

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
                            printf(" %lu moviendose sobre puente %d a velocidad %d, distancia: %d\n", data->thread_identificador, data->puente,data->velocidad, distancia_tmp);

                            sleep(data->velocidad);                                             // Simulo la velocidad
                            principal(data->puente,data->lado_izquierdo,0,0,1,distancia_tmp,0,data->tipo_carro);
                            distancia_tmp ++;
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
                            printf(" %lu moviendose sobre puente %d a velocidad %d, distancia: %d\n", data->thread_identificador, data->puente,data->velocidad, distancia_tmp);

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
                        // Aumento la distancia recorrida

                    }
                }
                else                    // Hay un carro en frente
                {

                    if(distancia_tmp == puente_tmp->capacidad)          // Ya termino de correrse todos los espacios disponibles
                    {

                        pthread_mutex_lock(&lock_thread_terminado);

                        //printf(ANSI_COLOR_YELLOW "Carro %lu termino de pasar el puente, habia alguien en frente %d\n" ANSI_COLOR_RESET, data->thread_identificador, puente_tmp->carros_circulando->tamanio);
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
                        printf(" %lu", data->thread_identificador);
                        printf(ANSI_COLOR_YELLOW " termino de pasar el puente %d, habia alguien al frente.\n" ANSI_COLOR_RESET, puente_tmp->thread_identificador);

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
                                while(i<195)
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
                                while(i<195)
                                {
                                    data->objeto.x -= 1;
                                    usleep(10000);
                                    i++;
                                }

                            }

                        }

                        eliminar_nodo_thread(threads,data->thread_identificador);           // Elimino el carro de la lista de hilos
                        eliminar_nodo_carro(buscar_nodo_thread(threads,data->puente)->puente->carros_circulando,data->thread_identificador);    // Elimino el carro de la lista de los carros circulando de su debido puente
                        buscar_nodo_thread(threads,data->puente)->puente->ocupancia -= 1;


                        thread_terminado = 1;
                        pthread_mutex_unlock(&lock_thread_terminado);


                        pthread_t id = pthread_self();
                        pthread_detach(id);
                        //return 0;

                    }
                    else
                    {

                        if(hardware == 1 && data->puente<3)
                        {

                            principal(data->puente,data->lado_izquierdo,0,0,1,distancia_tmp,1,data->tipo_carro);
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
                            printf(" %lu moviendose sobre puente %d a velocidad %d, distancia: %d\n", data->thread_identificador, data->puente,data->velocidad, distancia_tmp);

                            sleep(buscar_nodo_carro(puente_tmp->carros_circulando,data->thread_identificador)->prev->velocidad);
                            principal(data->puente,data->lado_izquierdo,0,0,1,distancia_tmp,0,data->tipo_carro);
                            distancia_tmp ++;
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
                            printf(" %lu moviendose sobre puente %d a velocidad %d, distancia: %d\n", data->thread_identificador, data->puente,data->velocidad, distancia_tmp);

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
                            sleep(buscar_nodo_carro(puente_tmp->carros_circulando,data->thread_identificador)->prev->velocidad);                                             // Simulo la velocidad
                            distancia_tmp ++;



                        }
                    }

                }
            }
            else    // Me dieron  el procesador pero aun no me ejecuto
            {

                pthread_mutex_lock(&lock_thread_terminado);

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
                printf(" %lu no puede moverse sobre puente %d\n", data->thread_identificador, distancia_tmp, data->puente);

                thread_terminado = 1;
                pthread_mutex_unlock(&lock_thread_terminado);

            }

        }

        usleep(10000);
    }
}




// Utiliza la lista global de los hilos para encontrar el puente en el que tiene que insertar carros
void *generador_carros(void *t)
{
    int i = 4;
    //pthread_t array [10000];
    double lambda = 1;
    float probabilidad = 0.0;
    double porcentaje_ambulancia = 0.0;
    int carros_max = getParameterValueConfigDouble("config_global.txt","carros_max");
    srand(time(NULL));
    while(i < carros_max)
    {

        //printf("Generando carro %lu de tipo %d al lado %d del puente %d \n",i, carro->tipo_carro, lado_random, puente_random);

        int puente_random = 0;

        if(hardware == 1)
        {
            puente_random = 1;//rand() % 3;
        }
        else
        {

            puente_random = rand() % 4;
        }

        int lado_random = rand() % 2;

        Thread_Carro carro = (Thread_Carro) calloc(1, sizeof(struct thread_carro));
        carro -> thread_identificador = i;
        carro -> corriendo = 0;
        carro -> puente = puente_random;
        carro -> pintado = 0;
        if(gui == 1)
        {
            carro -> velocidad = 0;//rand()%5;

        }
        else if(hardware == 1)
        {
            int velocidad = rand()%4;
            if(velocidad == 0)
            {
                velocidad ++;
            }
            carro -> velocidad = velocidad;
        }
        else
        {
            //carro -> velocidad = rand() / (RAND_MAX + 1.);
            int velocidad = rand()%2;
            if(velocidad == 0)
            {
                velocidad ++;
            }
            carro -> velocidad = velocidad;
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


        //printf("%lf\n", probabilidad);
        if(rand()%100 > probabilidad *100 )
        {
            carro -> tipo_carro = RADIOACTIVO;
            carro -> prioridad = 0;
            carro -> vida_carro = rand() % 30;
            carro -> limite_tiempo = rand() % 40;
        }

        else
        {
            if(rand()%100 > porcentaje_ambulancia*100)
            {
                carro -> tipo_carro = AMBULANCIA;
                carro -> prioridad = 1;
                carro -> vida_carro = rand() % 60;
                carro -> limite_tiempo = rand() % 80;
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

                carro->objeto.x = 180; //Extreme left of the window
            }
            else
            {
                carro->objeto.x = SCREEN_WIDTH - 225; //Extreme left of the window
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

            carro->objeto.h = 21;
            carro->objeto.w = 38;

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
            agregar_thread_prioridad(thread_nuevo,threads);// agregar_thread(thread_nuevo,threads)
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

        //usleep(60000);//usleep(600000); para regular
        if(hardware == 1)
        {

            sleep(1);
        }
        else
        {
            usleep(10000);// para semaforo
        }

        i++;
    }
}

