#include "main.h"
#include "rasp.h"
#include "calendarizador_rr.h"
#include "calendarizador_fcfs.h"
#include "calendarizador_sjf.h"
#include "calendarizador_real_time.h"
#include "calendarizador_priority_queue.h"
#include "algoritmos_control.h"
#include "manejo_carros.h"
#include "principal.h"
#include "control_puentes_hardware.h"
#include <time.h>


/*
* Metodo para ejecutar el hilo principal en caso de que GUI sea 1
*/
static int iniciarEjecucion(void *ptr)
{
    ejecutar();

    return 0;
}


/*
* Metodo para rpintar los vehiculos
*/
void pintar(Thread_Carro carro)
{

    if(carro->tipo_carro == RADIOACTIVO)
    {
        if(carro->lado_izquierdo == 1)
        {

            SDL_Surface* image_carro_lado_izquierdo = IMG_Load("carro_radioactivo_izquierda.png");
            carro->textura = SDL_CreateTextureFromSurface(SDL_GetRenderer(window), image_carro_lado_izquierdo);
            SDL_FreeSurface(image_carro_lado_izquierdo);
        }
        else
        {
            SDL_Surface* image_carro_lado_derecha = IMG_Load("carro_radioactivo_derecha.png");
            carro->textura = SDL_CreateTextureFromSurface(SDL_GetRenderer(window), image_carro_lado_derecha);
            SDL_FreeSurface(image_carro_lado_derecha);
        }


    }
    else if(carro->tipo_carro == AMBULANCIA)
    {
        if(carro->lado_izquierdo == 1)
        {
            SDL_Surface* image_carro_lado_izquierdo = IMG_Load("carro_ambulancia_izquierda.png");
            carro->textura = SDL_CreateTextureFromSurface(SDL_GetRenderer(window), image_carro_lado_izquierdo);
            SDL_FreeSurface(image_carro_lado_izquierdo);
        }
        else
        {
            SDL_Surface* image_carro_lado_derecha = IMG_Load("carro_ambulancia_derecha.png");
            carro->textura = SDL_CreateTextureFromSurface(SDL_GetRenderer(window), image_carro_lado_derecha);
            SDL_FreeSurface(image_carro_lado_derecha);
        }

    }
    else
    {
        if(carro->lado_izquierdo == 1)
        {
            SDL_Surface* image_carro_lado_izquierdo = IMG_Load("carro_regular_izquierda.png");
            carro->textura = SDL_CreateTextureFromSurface(SDL_GetRenderer(window), image_carro_lado_izquierdo);
            SDL_FreeSurface(image_carro_lado_izquierdo);
        }
        else
        {
            SDL_Surface* image_carro_lado_derecha = IMG_Load("carro_regular_derecha.png");
            carro->textura = SDL_CreateTextureFromSurface(SDL_GetRenderer(window), image_carro_lado_derecha);
            SDL_FreeSurface(image_carro_lado_derecha);
        }
    }

    carro->pintado = 1;

}


/*
* Entrada principal del sistema
*/
int main()
{
    thread_actual = -1;
    thread_terminado = 1;
    calendarizador = -1;
    hardware = 0;
    gui = 0;

    //carros_ui = calloc(1,sizeof(struct thread_list_carro));

    hardware = getParameterValueConfig("config_global.txt","hardware");
    if(hardware == 1)
    {
        printf("Hardware ENABLED\n");
//        int g,rep;

        // Set up gpi pointer for direct register access
        setup_io();
        set_outputRasp();

        pthread_create(&thread_puente_hardware_0, NULL, Estado_P1, NULL);
        pthread_create(&thread_puente_hardware_1, NULL, Estado_P2, NULL);
        pthread_create(&thread_puente_hardware_2, NULL, Estado_P3, NULL);


        pthread_create(&thread_puente_hardware_0_lados, NULL, hardware_0_lados, NULL);
        pthread_create(&thread_puente_hardware_1_lados, NULL, hardware_1_lados, NULL);
        pthread_create(&thread_puente_hardware_2_lados, NULL, hardware_2_lados, NULL);

    }

    gui = getParameterValueConfig("config_global.txt","interfaz");
    if(gui == 1)
    {
        printf("Ejecutando GUI\n");
        //pthread_create(&thread_puente_software_0_lados, NULL, software_0_lados, NULL);
        SCREEN_WIDTH = 802;
        SCREEN_HEIGHT = 680;

        int quit = 0;

        SDL_Init(SDL_INIT_EVERYTHING);
        //For loading PNG images
        IMG_Init(IMG_INIT_PNG);
        window = SDL_CreateWindow("Animated Thread Bridge", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Event input;

//        SDL_Thread* threadID2 =
        SDL_CreateThread( iniciarEjecucion, "iniciarEjecucion",(void *)NULL);

        SDL_Texture* textura_fondo = NULL;

        SDL_Surface* fondo_temp = IMG_Load("bg.png");
        textura_fondo = SDL_CreateTextureFromSurface(renderer, fondo_temp);


        //Deleting the temporary surface
        SDL_FreeSurface(fondo_temp);

        SDL_Rect fondo;
        fondo.x = 0; //Extreme left of the window
        fondo.y = 0; //Very bottom of the window
        fondo.w = SCREEN_WIDTH; //100 pixels width
        fondo.h = SCREEN_HEIGHT; //100 pixels height

        while (!quit)
        {
            while (SDL_PollEvent(&input) > 0)
            {
                if (input.type == SDL_QUIT) quit = 1;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, textura_fondo, NULL, &fondo);

            Thread temporal = threads->head;
            while(1)
            {
                if(threads != NULL)
                {
                    if(threads->head != NULL)
                    {
                        //printf("Aqui %lu\n", temporal->thread_identificador);
                        if(temporal->thread_identificador>3)
                        {

                            if(temporal->carro->pintado == 0){

                                pintar(temporal->carro);
                            } else {
                                SDL_RenderCopy(renderer, temporal->carro->textura, NULL, &temporal->carro->objeto);
                            }
                        }
                      /*  else
                        {
                            break;
                        }*/

                        if(temporal->next != NULL)
                        {
                            //printf("next \n");
                            temporal = temporal->next;      // Obtengo el siguiente
                        }
                        else
                        {
                            break;
                        }

                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }

            SDL_RenderPresent(renderer);
            //usleep(100000);
            SDL_Delay( 10);
        }

        //Deleting the texture
        SDL_DestroyTexture(textura_fondo);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);

        //For quitting IMG systems
        IMG_Quit();
        SDL_Quit();
    }
    else
    {
        ejecutar();         // Inicia ejecucion principal
    }

    return 0;
}






