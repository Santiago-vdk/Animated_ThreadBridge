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

        SCREEN_WIDTH = 802;
        SCREEN_HEIGHT = 680;

        int quit = 0;

        SDL_Init(SDL_INIT_EVERYTHING);

        IMG_Init(IMG_INIT_PNG);
        window = SDL_CreateWindow("Animated Thread Bridge", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Event input;


        SDL_CreateThread( iniciarEjecucion, "iniciarEjecucion",(void *)NULL);

        SDL_Texture* textura_fondo = NULL;

        SDL_Surface* fondo_temp = IMG_Load("bg.png");
        textura_fondo = SDL_CreateTextureFromSurface(renderer, fondo_temp);


//getParameterValueConfig("config_global.txt","calendarizador");

        TTF_Init();

        TTF_Font* Sans = TTF_OpenFont( "FreeSans.ttf", 18); //this opens a font style and sets a size
        if(Sans == NULL)
        {
            printf("Fuck \n");
        }

        SDL_Color black = {0, 0, 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

        int metodo = getParameterValueConfig("config_puente_0.txt","metodo_control");
        SDL_Surface* metodo_puente_0_mensaje;
        if(metodo == 0)
        {
            metodo_puente_0_mensaje = TTF_RenderText_Solid(Sans, "Oficial de Transito", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        }
        else if(metodo == 1)
        {
            metodo_puente_0_mensaje = TTF_RenderText_Solid(Sans, "Semaforo", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        }
        else
        {
            metodo_puente_0_mensaje = TTF_RenderText_Solid(Sans, "Jungle Law", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        }
        SDL_Texture* metodo_puente_0 = SDL_CreateTextureFromSurface(renderer, metodo_puente_0_mensaje); //now you can convert it into a texture

        SDL_Rect metodo_puente_0_rect; //create a rect
        metodo_puente_0_rect.x = 100;  //controls the rect's x coordinate
        metodo_puente_0_rect.y = 30; // controls the rect's y coordinte
        metodo_puente_0_rect.w = metodo_puente_0_mensaje->w; // controls the width of the rect
        metodo_puente_0_rect.h = metodo_puente_0_mensaje->h;// controls the height of the rect

        SDL_FreeSurface(metodo_puente_0_mensaje);






        metodo = getParameterValueConfig("config_puente_1.txt","metodo_control");
        SDL_Surface* metodo_puente_1_mensaje;
        if(metodo == 0)
        {
            metodo_puente_1_mensaje = TTF_RenderText_Solid(Sans, "Oficial de Transito", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        }
        else if(metodo == 1)
        {
            metodo_puente_1_mensaje = TTF_RenderText_Solid(Sans, "Semaforo", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        }
        else
        {
            metodo_puente_1_mensaje = TTF_RenderText_Solid(Sans, "Jungle Law", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        }
        SDL_Texture* metodo_puente_1 = SDL_CreateTextureFromSurface(renderer, metodo_puente_1_mensaje); //now you can convert it into a texture

        SDL_Rect metodo_puente_1_rect; //create a rect
        metodo_puente_1_rect.x = 100;  //controls the rect's x coordinate
        metodo_puente_1_rect.y = 50; // controls the rect's y coordinte
        metodo_puente_1_rect.w = metodo_puente_1_mensaje->w; // controls the width of the rect
        metodo_puente_1_rect.h = metodo_puente_1_mensaje->h;// controls the height of the rect

        SDL_FreeSurface(metodo_puente_1_mensaje);




        metodo = getParameterValueConfig("config_puente_2.txt","metodo_control");
        SDL_Surface* metodo_puente_2_mensaje;
        if(metodo == 0)
        {
            metodo_puente_2_mensaje = TTF_RenderText_Solid(Sans, "Oficial de Transito", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        }
        else if(metodo == 1)
        {
            metodo_puente_2_mensaje = TTF_RenderText_Solid(Sans, "Semaforo", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        }
        else
        {
            metodo_puente_2_mensaje = TTF_RenderText_Solid(Sans, "Jungle Law", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        }
        SDL_Texture* metodo_puente_2 = SDL_CreateTextureFromSurface(renderer, metodo_puente_2_mensaje); //now you can convert it into a texture

        SDL_Rect metodo_puente_2_rect; //create a rect
        metodo_puente_2_rect.x = 100;  //controls the rect's x coordinate
        metodo_puente_2_rect.y = 73; // controls the rect's y coordinte
        metodo_puente_2_rect.w = metodo_puente_2_mensaje->w; // controls the width of the rect
        metodo_puente_2_rect.h = metodo_puente_2_mensaje->h;// controls the height of the rect

        SDL_FreeSurface(metodo_puente_2_mensaje);



        metodo = getParameterValueConfig("config_puente_3.txt","metodo_control");
        SDL_Surface* metodo_puente_3_mensaje;
        if(metodo == 0)
        {
            metodo_puente_3_mensaje = TTF_RenderText_Solid(Sans, "Oficial de Transito", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        }
        else if(metodo == 1)
        {
            metodo_puente_3_mensaje = TTF_RenderText_Solid(Sans, "Semaforo", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        }
        else
        {
            metodo_puente_3_mensaje = TTF_RenderText_Solid(Sans, "Jungle Law", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

        }
        SDL_Texture* metodo_puente_3 = SDL_CreateTextureFromSurface(renderer, metodo_puente_3_mensaje); //now you can convert it into a texture

        SDL_Rect metodo_puente_3_rect; //create a rect
        metodo_puente_3_rect.x = 100;  //controls the rect's x coordinate
        metodo_puente_3_rect.y = 95; // controls the rect's y coordinte
        metodo_puente_3_rect.w = metodo_puente_3_mensaje->w; // controls the width of the rect
        metodo_puente_3_rect.h = metodo_puente_3_mensaje->h;// controls the height of the rect

        SDL_FreeSurface(metodo_puente_3_mensaje);


        metodo = getParameterValueConfig("config_global.txt","calendarizador");
        SDL_Surface* mensaje_calendarizador;


        switch (calendarizador )
        {
        case 0:
            mensaje_calendarizador = TTF_RenderText_Solid(Sans, "Round Robin", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
            break;
        case 1:
            mensaje_calendarizador = TTF_RenderText_Solid(Sans, "FCFS", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

            break;
        case 2:
            mensaje_calendarizador = TTF_RenderText_Solid(Sans, "SJF", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

            break;
        case 3:
            mensaje_calendarizador = TTF_RenderText_Solid(Sans, "Prio. Queue", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

            break;
        case 4:
            mensaje_calendarizador = TTF_RenderText_Solid(Sans, "Real Time", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

            break;
        default:
            mensaje_calendarizador = TTF_RenderText_Solid(Sans, "Round Robin", black); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
            break;
        }

        SDL_Texture* textura_calendarizador = SDL_CreateTextureFromSurface(renderer, mensaje_calendarizador); //now you can convert it into a texture

        SDL_Rect calendarizador_rect; //create a rect
        calendarizador_rect.x = 680;  //controls the rect's x coordinate
        calendarizador_rect.y = 30; // controls the rect's y coordinte
        calendarizador_rect.w = mensaje_calendarizador->w; // controls the width of the rect
        calendarizador_rect.h = mensaje_calendarizador->h;// controls the height of the rect

        SDL_FreeSurface(mensaje_calendarizador);






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
            SDL_RenderCopy(renderer, metodo_puente_0, NULL, &metodo_puente_0_rect);
            SDL_RenderCopy(renderer, metodo_puente_1, NULL, &metodo_puente_1_rect);
            SDL_RenderCopy(renderer, metodo_puente_2, NULL, &metodo_puente_2_rect);
            SDL_RenderCopy(renderer, metodo_puente_3, NULL, &metodo_puente_3_rect);
            SDL_RenderCopy(renderer, textura_calendarizador, NULL, &calendarizador_rect);

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

                            if(temporal->carro->pintado == 0)
                            {

                                pintar(temporal->carro);
                            }
                            else
                            {
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
        TTF_Quit();
    }
    else
    {
        ejecutar();         // Inicia ejecucion principal
    }

    return 0;
}






