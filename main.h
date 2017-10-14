#include <stdio.h>
#include <stdlib.h>
#include "thread_data.h"
#include <time.h>
#include "puentes.h"
#include <unistd.h>
#include <math.h>
#include "lector_archivos.h"
#include "pthread.h"

#include <fcntl.h>
#include <sys/mman.h>

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

long thread_actual;
int thread_terminado;
int calendarizador;
int hardware;
int gui;

pthread_t thread_calendarizador;
pthread_t thread_generador_carros;

pthread_t thread_puente_hardware_0;
pthread_t thread_puente_hardware_1;
pthread_t thread_puente_hardware_2;

pthread_t thread_puente_hardware_0_lados;
pthread_t thread_puente_hardware_1_lados;
pthread_t thread_puente_hardware_2_lados;

pthread_t thread_puente_software_0_lados;

pthread_mutex_t lock_thread_terminado;
pthread_mutex_t lock_thread_actual;
pthread_mutex_t lock_contador_tmp;
pthread_mutex_t lock_carro_movimiento;
pthread_mutex_t lock_modificar_lista;

pthread_mutex_t lock_comenzar_espera;
pthread_mutex_t lock_agregarse;

ThreadList threads;
ThreadListPuente puentes;



SDL_Window* window;


//Screen dimension constants
int SCREEN_WIDTH;
int SCREEN_HEIGHT;




#endif // MAIN_H_INCLUDED
