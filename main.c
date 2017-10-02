#include "main.h"
#include "calendarizador_rr.h"
#include "calendarizador_fcfs.h"
#include "calendarizador_sjf.h"
#include "calendarizador_real_time.h"
#include "calendarizador_priority_queue.h"
#include "algoritmos_control.h"
#include "manejo_carros.h"
#include "rasp.h"
#include "principal.h"
#include "control_puentes_hardware.h"



void * threadFunction( void* data )   //Print incoming data
{


        ejecutar();         // Inicia ejecucion principal




}


int main()
{
    thread_actual = -1;
    thread_terminado = 1;
    calendarizador = -1;
    hardware = 0;
    gui = 0;

    carros_ui = calloc(1,sizeof(struct thread_list_carro));

    hardware = getParameterValueConfig("config_global.txt","hardware");
    if(hardware == 1)
    {
        printf("Hardware ENABLED\n");
        int g,rep;

        // Set up gpi pointer for direct register access
        setup_io();
        set_outputRasp();
        pthread_create(&thread_puente_hardware_0, NULL, Estado_P1, NULL);
//        pthread_create(&thread_puente_hardware_1, NULL , Estado_P1 , NULL);
//        pthread_create(&thread_puente_hardware_2, NULL , Estado_P2 , NULL);


        pthread_create(&thread_puente_hardware_0_lados, NULL, hardware_0_lados, NULL);
//        pthread_create(&thread_puente_hardware_1_lados, NULL , hardware_1_lados , NULL);
//        pthread_create(&thread_puente_hardware_2_lados, NULL , hardware_2_lados , NULL);

    }

    gui = getParameterValueConfig("config_global.txt","interfaz");
    if(gui == 1)
    {
        printf("Ejecutando GUI\n");

        SCREEN_WIDTH = 802;
        SCREEN_HEIGHT = 680;

        int quit = 0;


        SDL_Init(SDL_INIT_EVERYTHING);
        //For loading PNG images
        IMG_Init(IMG_INIT_PNG);
        window = SDL_CreateWindow("Animated RKT Bridge", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Event input;

 //SDL_Thread* threadID = SDL_CreateThread( threadFunction, "MainThread", NULL);

        pthread_t mainThread;
        pthread_create(&mainThread, NULL, threadFunction, NULL);

        SDL_Texture* textura_fondo = NULL;

        SDL_Surface* fondo_temp = IMG_Load("bg.png");
        textura_fondo = SDL_CreateTextureFromSurface(renderer, fondo_temp);

        /*      SDL_Texture* texture2 = NULL;
              SDL_Surface* image_carro_lado_izquierdo = IMG_Load("carro regular izquierda.png");
              texture2 = SDL_CreateTextureFromSurface(renderer, image_carro_lado_izquierdo);
              SDL_FreeSurface(image_carro_lado_izquierdo);*/

        //Deleting the temporary surface
        SDL_FreeSurface(fondo_temp);

        SDL_Rect fondo;
        fondo.x = 0; //Extreme left of the window
        fondo.y = 0; //Very bottom of the window
        fondo.w = SCREEN_WIDTH; //100 pixels width
        fondo.h = SCREEN_HEIGHT; //100 pixels height
        //SDL_Thread* pintadoThreadID = SDL_CreateThread( pintarFunction, "PintarThread", NULL);


        Thread temporal = threads->head;
        while (!quit)
        {
            while (SDL_PollEvent(&input) > 0)
            {
                if (input.type == SDL_QUIT) quit = 1;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            SDL_RenderCopy(renderer, textura_fondo, NULL, &fondo);

            if(carros_ui->head != NULL)
            {
                Thread_Carro carro_tmp = carros_ui->head;
                for(int i = 0; i < carros_ui->tamanio; i++)
                {



                    SDL_RenderCopy(renderer, carro_tmp->textura, NULL, &carro_tmp->objeto);

                    if(carro_tmp->next != NULL)
                    {
                        carro_tmp = carro_tmp->next;
                    }
                    else
                    {
                        break;
                    }


                }


            }

            SDL_RenderPresent(renderer);
            //usleep(100000);
            SDL_Delay( 1);
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






