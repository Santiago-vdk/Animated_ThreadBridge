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

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//Screen dimension constants
const int SCREEN_WIDTH = 802;
const int SCREEN_HEIGHT = 680;


int posX = 0;
SDL_Rect rect2;
SDL_Texture* texture2 = NULL;

SDL_Rect rect2_1;
SDL_Texture* texture2_1 = NULL;

SDL_Rect rect2_2;
SDL_Texture* texture2_2 = NULL;

SDL_Rect rect2_3;
SDL_Texture* texture2_3 = NULL;


// Derecha
SDL_Rect rect3;
SDL_Texture* texture3 = NULL;

// Derecha
SDL_Rect rect3_1;
SDL_Texture* texture3_1 = NULL;


// Derecha
SDL_Rect rect3_2;
SDL_Texture* texture3_2 = NULL;


// Derecha
SDL_Rect rect3_3;
SDL_Texture* texture3_3 = NULL;


void move()
{
    if(rect2.x > 195 && rect2.x < 205)
    {
        rect2.x += 1;
        rect2.y += 2;
        usleep(10000);
    }
    else if(rect2.x > 545 && rect2.x < 555)
    {
        rect2.x += 1;
        rect2.y -= 2;
        usleep(10000);
    }
    else
    {
        usleep(10000);
        rect2.x += 1;
    }
}

void moveDerecha()
{
    if(rect3.x > 545 && rect3.x < 555)
    {

        rect3.x -= 1;
        rect3.y -= 2;
        usleep(10000);
    }
    else  if(rect3.x > 195 && rect3.x < 205)
    {
        rect3.x -= 1;
        rect3.y += 2;
        usleep(10000);
    }
    else
    {
        usleep(10000);
        rect3.x -= 1;
    }
}



int threadFunction( void* data )   //Print incoming data
{

    while(1)
    {
        ejecutar();         // Inicia ejecucion principal
    }

    return 0;

}


int main()
{
    thread_actual = -1;
    thread_terminado = 1;
    calendarizador = -1;
    hardware = 0;
    gui = 0;


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

        SDL_Init(SDL_INIT_EVERYTHING);
        //For loading PNG images
        IMG_Init(IMG_INIT_PNG);
        SDL_Window* window = SDL_CreateWindow("Animated RKT Bridge", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_Event input;
        int quit = 0;

        SDL_Thread* threadID = SDL_CreateThread( threadFunction, "MainThread", NULL);
        SDL_Texture* texture = NULL;
        SDL_Surface* temp = IMG_Load("bg.png");

        //Filling texture with the image using a surface
        texture = SDL_CreateTextureFromSurface(renderer, temp);

        SDL_Surface* image = IMG_Load("carro regular izquierda.png");
        texture2 = SDL_CreateTextureFromSurface(renderer, image);

        SDL_Surface* image_1 = IMG_Load("carro regular izquierda.png");
        texture2_1 = SDL_CreateTextureFromSurface(renderer, image_1);

        SDL_Surface* image_2 = IMG_Load("carro regular izquierda.png");
        texture2_2 = SDL_CreateTextureFromSurface(renderer, image_2);

        SDL_Surface* image_3 = IMG_Load("carro regular izquierda.png");
        texture2_3 = SDL_CreateTextureFromSurface(renderer, image_3);

        SDL_Surface* image3 = IMG_Load("carro regular derecha.png");
        texture3 = SDL_CreateTextureFromSurface(renderer, image3);

        SDL_Surface* image3_1 = IMG_Load("carro regular derecha.png");
        texture3_1 = SDL_CreateTextureFromSurface(renderer, image3_1);

        SDL_Surface* image3_2 = IMG_Load("carro regular derecha.png");
        texture3_2 = SDL_CreateTextureFromSurface(renderer, image3_2);

        SDL_Surface* image3_3 = IMG_Load("carro regular derecha.png");
        texture3_3 = SDL_CreateTextureFromSurface(renderer, image3_3);

        //Deleting the temporary surface
        SDL_FreeSurface(temp);
        SDL_FreeSurface(image);
        SDL_FreeSurface(image_1);
        SDL_FreeSurface(image_2);
        SDL_FreeSurface(image_3);
        SDL_FreeSurface(image3);

        SDL_Rect rect;
        rect.x = 0; //Extreme left of the window
        rect.y = 0; //Very bottom of the window
        rect.w = SCREEN_WIDTH; //100 pixels width
        rect.h = SCREEN_HEIGHT; //100 pixels height

        rect2.x = posX; //Extreme left of the window
        rect2.y = 580; //Very bottom of the window
        rect2.w = 38; //100 pixels width
        rect2.h = 21; //100 pixels height

        rect2_1.x = posX; //Extreme left of the window
        rect2_1.y = 435; //Very bottom of the window
        rect2_1.w = 38; //100 pixels width
        rect2_1.h = 21; //100 pixels height

        rect2_2.x = posX; //Extreme left of the window
        rect2_2.y = 298; //Very bottom of the window
        rect2_2.w = 38; //100 pixels width
        rect2_2.h = 21; //100 pixels height

        rect2_3.x = posX; //Extreme left of the window
        rect2_3.y = 165; //Very bottom of the window
        rect2_3.w = 38; //100 pixels width
        rect2_3.h = 21; //100 pixels height

        rect3.x = 750; //Extreme left of the window
        rect3.y = 630; //Very bottom of the window
        rect3.w = 38; //100 pixels width
        rect3.h = 21; //100 pixels height

        rect3_1.x = 750; //Extreme left of the window
        rect3_1.y = 485; //Very bottom of the window
        rect3_1.w = 38; //100 pixels width
        rect3_1.h = 21; //100 pixels height

        rect3_2.x = 750; //Extreme left of the window
        rect3_2.y = 345; //Very bottom of the window
        rect3_2.w = 38; //100 pixels width
        rect3_2.h = 21; //100 pixels height

        rect3_3.x = 750; //Extreme left of the window
        rect3_3.y = 215; //Very bottom of the window
        rect3_3.w = 38; //100 pixels width
        rect3_3.h = 21; //100 pixels height

        TTF_Init();
        TTF_Font* Sans = TTF_OpenFont( "FreeSans.ttf", 18); //this opens a font style and sets a size
        SDL_Color White = {0, 0, 0};  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

        SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "Semaforo", White); // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first
        SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage); //now you can convert it into a texture

        SDL_Rect Message_rect; //create a rect
        Message_rect.x = 100;  //controls the rect's x coordinate
        Message_rect.y = 30; // controls the rect's y coordinte
        Message_rect.w = surfaceMessage->w; // controls the width of the rect
        Message_rect.h = surfaceMessage->h;// controls the height of the rect

        SDL_FreeSurface(surfaceMessage);

        while (!quit)
        {
            while (SDL_PollEvent(&input) > 0)
            {
                if (input.type == SDL_QUIT) quit = 1;
            }

            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            move();
            moveDerecha();
            //Render current frame

            //Copying the texture on to the window using renderer and rectangle
            SDL_RenderCopy(renderer, texture, NULL, &rect);

            if(rect2.x > SCREEN_WIDTH)
            {
                SDL_DestroyTexture(texture2);
            }
            else
            {
                SDL_RenderCopy(renderer, texture2, NULL, &rect2);
            }

            SDL_RenderCopy(renderer, texture2_1, NULL, &rect2_1);
            SDL_RenderCopy(renderer, texture2_2, NULL, &rect2_2);
            SDL_RenderCopy(renderer, texture2_3, NULL, &rect2_3);
            SDL_RenderCopy(renderer, texture3, NULL, &rect3);
            SDL_RenderCopy(renderer, texture3_1, NULL, &rect3_1);
            SDL_RenderCopy(renderer, texture3_2, NULL, &rect3_2);
            SDL_RenderCopy(renderer, texture3_3, NULL, &rect3_3);
            SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
            SDL_RenderPresent(renderer);

        }

        //Deleting the texture
        SDL_DestroyTexture(texture);

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






