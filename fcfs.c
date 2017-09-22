
#include "round_robin.h"
#include "thread_data.h"
#include "globales.h"

void ejecutar(Puente puente, ThreadList lado_izq, ThreadList lado_der, int control, int k)
{

    ThreadList lado_izq;
    ThreadList lado_der;
    int semaforo_tmp = SEMAFORO;
    int semaforo_izq = 1; // Izquierdo comienza encendido
    int semaforo_der = 0; // Derecho comienza apagado

    while (1)
    {
        if (control == OFICIAL)
        {
            int radioactivos_izq = buscarRadioactivos(lado_iz);
            int radioactivos_der = buscarRadioactivos(lado_der);

            // Hay mas radioactivos del lado izquierdo
            if (radioactivos_izq > radioactivos_der)
            {
                // Proceso lado izquierdo
                for (int carros_izq = 0; carros_izq < k; carros_izq++)
                {
                    // Puente lleno
                    if (puente - > occupancy == puente - > capacity)
                    {
                        printf("Esperando que terminen carros del lado derecho");
                    }
                    // Puente con campo
                    else
                    {
                        Thread_Carro_Puente tmp = getNode(lado_izq, carros_izq); // Agarro carro del lado izquierdo
                        tmp - > corriendo = true;
                        popNode(lado_izq, carros_izq);
                        addNode(tmp, puente - > current_cars);
                    }
                }
            }
            else
            {
                // Proceso lado derecho
                for (int carros_der = 0; carros_der < k; carros_der++)
                {
                    // Puente lleno
                    if (puente - > occupancy == puente - > capacity)
                    {
                        printf("Esperando que terminen carros del lado izquierdo");
                    }
                    // Puente con campo
                    else
                    {
                        Thread_Carro_Puente tmp = getNode(lado_der, carros_der); // Agarro carro del lado izquierdo
                        tmp - > corriendo = true;
                        popNode(lado_der, carros_der);
                        addNode(tmp, puente - > current_cars);
                    }
                }

            }

        }
        else if (control == SEMAFORO)
        {
            semaforo_tmp = SEMAFORO;

            // izquierda en verde y derecha en rojo
            if (semaforo_izq == 1 && semaforo_der == 0)
            {
                // Proceso lado izquierdo
                while (semaforo_tmp > 0)
                {
                    if (puente - > occupancy == puente - > capacity) // Puente lleno
                    {
                        printf("Esperando que terminen carros del lado derecho");
                    }
                    else   // Puente con campo
                    {
                        Thread_Carro_Puente tmp = getNode(lado_izq, carros_izq); // Agarro carro del lado izquierdo
                        popNode(lado_izq, carros_izq); // Lo saco del lado izquierdo
                        tmp - > corriendo = true; // Le digo al carro que se puede mover
                        addNode(tmp, puente - > current_cars); // Lo agrego a los carros que estan en el puente
                    }
                    sleep(1);
                    semaforo_tmp--;
                }
                semaforo_der = 1; // Cambio el semaforo a verde del lado derecho
                semaforo_izq = 0; // Cambio el semaforo a rojo del lado izquierdo

            }
            else if (semaforo_izq == 0 && semaforo_der == 1)   // izquierda en rojo y derecha en verde
            {

                // Proceso lado izquierdo
                while (semaforo_tmp > 0)
                {
                    if (puente - > occupancy == puente - > capacity) // Puente lleno
                    {
                        printf("Esperando que terminen carros del lado derecho");
                    }
                    else   // Puente con campo
                    {
                        Thread_Carro_Puente tmp = getNode(lado_der, carros_der); // Agarro carro del lado derecho
                        popNode(lado_der, carros_der); // Lo saco del lado derecho
                        tmp - > corriendo = true; // Le digo al carro que se puede mover
                        addNode(tmp, puente - > current_cars); // Lo agrego a los carros que estan en el puente
                    }
                    sleep(1);
                    semaforo_tmp--;
                }
                semaforo_der = 0; // Cambio el semaforo a verde del lado derecho
                semaforo_izq = 1; // Cambio el semaforo a rojo del lado izquierdo
            }
            else
            {
                printf("Error a la hora de realizar cambios en semaforos \n");
            }

        }
        else
        {

            int radioactivos_izq = buscarRadioactivos(lado_iz);
            int radioactivos_der = buscarRadioactivos(lado_der);
            srand(time(NULL));

            int random = rand() % 50;
            // Hay mas radioactivos del lado izquierdo
            if (radioactivos_izq*random > radioactivos_der*random)
            {
                // Proceso lado izquierdo
                for (int carros_izq = 0; carros_izq < k; carros_izq++)
                {
                    // Puente lleno
                    if (puente - > occupancy == puente - > capacity)
                    {
                        printf("Esperando que terminen carros del lado derecho");
                    }
                    // Puente con campo
                    else
                    {
                        Thread_Carro_Puente tmp = getNode(lado_izq, carros_izq); // Agarro carro del lado izquierdo
                        tmp - > corriendo = true;
                        popNode(lado_izq, carros_izq);
                        addNode(tmp, puente - > current_cars);
                    }
                }
            }
            else
            {
                // Proceso lado derecho
                for (int carros_der = 0; carros_der < k; carros_der++)
                {
                    // Puente lleno
                    if (puente - > occupancy == puente - > capacity)
                    {
                        printf("Esperando que terminen carros del lado izquierdo");
                    }
                    // Puente con campo
                    else
                    {
                        Thread_Carro_Puente tmp = getNode(lado_der, carros_der); // Agarro carro del lado izquierdo
                        tmp - > corriendo = true;
                        popNode(lado_der, carros_der);
                        addNode(tmp, puente - > current_cars);
                    }
                }

            }


        }

    }
}
