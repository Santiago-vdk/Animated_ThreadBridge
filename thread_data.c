#include <stdlib.h>
#include <stdio.h>
#include "thread_data.h"

void agregar_puente(Thread_Puente node, ThreadListPuente list)
{
    node->prev = NULL;
    node->next = NULL;
    node->prev = NULL;
    node->next = NULL;
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        list->tamanio += 1;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
        list->tamanio += 1;
    }
}

void agregar_carro(Thread_Carro node, ThreadListCarro list)
{
    node->prev = NULL;
    node->next = NULL;
    node->prev = NULL;
    node->next = NULL;
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        list->tamanio += 1;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
        list->tamanio += 1;
    }

    switch(node->tipo_carro)
    {
    case AMBULANCIA:
        list->cantidad_ambulancias += 1;
        break;

    case RADIOACTIVO:
        list->cantidad_radioactivos += 1;
        break;
    }

}

void agregar_thread(Thread node, ThreadList list)
{

    node->prev = NULL;
    node->next = NULL;
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        list->tamanio += 1;
    }
    else
    {
        list->tail->next = node;
        node->prev = list->tail;
        list->tail = node;
        list->tamanio += 1;
    }

}

Thread_Carro pop_primer_thread_carro(ThreadListCarro list)
{
    if (list->head != NULL)
    {
        Thread_Carro tmp = list->head;

        if(tmp->next == NULL)
        {
            list->head = NULL;
            list->tail = NULL;
            list->tamanio -= 1;

        }
        else
        {
            tmp->next->prev = NULL;
            list->head = tmp->next;
            tmp->next = NULL;
            list->tamanio -= 1;

        }
        return tmp;

    }
    else
    {
        printf("Lista vacia\n");
        return NULL;
    }

}

Thread pop_primer_thread(ThreadList list)
{
    if (list->head != NULL)
    {
        Thread tmp = list->head;

        if(tmp->next == NULL)
        {
            list->head = NULL;
            list->tail = NULL;
            list->tamanio -= 1;

        }
        else
        {
            tmp->next->prev = NULL;
            list->head = tmp->next;
            tmp->next = NULL;
            list->tamanio -= 1;

        }
        return tmp;

    }
    else
    {
        printf("Lista vacia\n");
        return NULL;
    }

}


Thread buscar_nodo_thread(ThreadList list, long thread_identificador)
{
    if (list->head->thread_identificador == thread_identificador)
    {
        return list-> head;
    }
    else
    {
        Thread tmp = list->head;
        while (tmp->thread_identificador != thread_identificador)
        {

            tmp = tmp->next;
            if (!tmp)
            {
                return NULL;
            }
        }
        return tmp;
    }
}


Thread_Carro buscar_nodo_carro(ThreadListCarro list, long thread_identificador)
{
    if (list->head->thread_identificador == thread_identificador)
    {
        return list-> head;
    }
    else
    {
        Thread_Carro tmp = list->head;
        while (tmp->thread_identificador != thread_identificador)
        {

            tmp = tmp->next;
            if (!tmp)
            {
                return NULL;
            }
        }
        return tmp;
    }
}

Thread_Puente buscar_nodo_puente(ThreadListPuente list, long thread_identificador)
{
    if (list->head->thread_identificador == thread_identificador)
    {
        return list-> head;
    }
    else
    {
        Thread_Puente tmp = list->head;
        while (tmp->thread_identificador != thread_identificador)
        {

            tmp = tmp->next;
            if (!tmp)
            {
                return NULL;
            }
        }
        return tmp;
    }

}

/* Removes a thread node from the list */
void eliminar_nodo_thread(ThreadList list, long thread_identificador)
{
    if (list->head == NULL)
    {
        printf("Thread list carro is empty\n");
    }
    else
    {
        Thread tmp = list->head;

        if(list->head == list->tail && tmp->thread_identificador == thread_identificador)
        {
            list->head = NULL;
            list->tail = NULL;
            list->tamanio-=1;
        }
        else
        {

            if (tmp->thread_identificador == thread_identificador)
            {
                list->head = tmp->next;     // La cabeza va a ser el siguiente
                if(list->head != NULL)
                {
                    list->head->prev = NULL;
                }
                free(tmp);
                list->tamanio-=1;
            }
            else
            {
                while (tmp->next != NULL)
                {
                    if (tmp->next->thread_identificador == thread_identificador)
                    {
                        Thread tmp2 = tmp->next;
                        if (tmp->next->next != NULL)
                        {
                            tmp->next = tmp->next->next;
                            tmp->next->prev = tmp;
                            list->tamanio-=1;
                            free(tmp2);
                            break;
                        }
                        else //eliminar tail
                        {

                            tmp->next = NULL;
                            list->tail=tmp;
                            list->tamanio-=1;
                            free(tmp2);
                            break;
                        }
                    }
                    tmp = tmp->next;
                }
            }
        }
    }
}

/* Removes a thread node from the list */
void eliminar_nodo_carro(ThreadListCarro list, long thread_identificador)
{
    if (list->head == NULL)
    {
        printf("Thread list carro is empty\n");
    }
    else
    {
        Thread_Carro tmp = list->head;

        if(list->head == list->tail && tmp->thread_identificador == thread_identificador)
        {
            list->head = NULL;
            list->tail = NULL;
            list->tamanio-=1;
        }
        else
        {
            if (tmp->thread_identificador == thread_identificador)
            {
                list->head = tmp->next;     // La cabeza va a ser el siguiente
                if(list->head != NULL)
                {
                    list->head->prev = NULL;
                }
                //free(tmp);            extraño
                list->tamanio-=1;
            }
            else
            {
                while (tmp->next != NULL)
                {
                    if (tmp->next->thread_identificador == thread_identificador)
                    {
//                        Thread_Carro tmp2 = tmp->next;
                        if (tmp->next->next != NULL)
                        {
                            tmp->next = tmp->next->next;
                            tmp->next->prev = tmp;
                            list->tamanio-=1;
                            //free(tmp2);       extraño
                            break;
                        }
                        else //eliminar tail
                        {
                            tmp->next = NULL;
                            list->tail=tmp;
                            list->tamanio-=1;
                            //free(tmp2);           extraño
                            break;
                        }
                    }
                    tmp = tmp->next;
                }
            }
        }
    }
}

/**
 * Imprime cada uno de los nodos
 **/
void imprimir(ThreadListCarro pLista){
    printf("\n-------- LISTA CARRO -------\n");
    Thread_Carro tmp = pLista->head;

    while(tmp != NULL) {
        printf("\nCarro: %lu, Tipo: %d, Prioridad: %d, Tiempo Limite: %d\n",tmp->thread_identificador, tmp->tipo_carro, tmp->prioridad, tmp->limite_tiempo);
        tmp = tmp->next;
        sleep(1);
    }
    printf("\n----------------------------\n\n");
}

/**
 * Aumenta en una unidad la prioridad de cada elemento de la lista.
 */
void Envejecer(ThreadListCarro list)
{
    Thread_Carro tmp = list->head;
    int largo = list->tamanio;
    for (int indice = 0; indice < largo; indice++)
    {
        if(tmp->prioridad > 0){
            tmp->prioridad -= 1;
            tmp = tmp->next;
        }
    }
}


void Envejecer_Threads(ThreadList list)
{
    Thread tmp = list->head;
    int largo = list->tamanio;
    for (int indice = 0; indice < largo; indice++)
    {
        if(tmp->prioridad > 0){
            tmp->prioridad -= 1;
            tmp = tmp->next;
        }
    }
}

/**
 * Elimina la cabeza de la lista como parametro.
 */
Thread_Carro popCar(ThreadListCarro list)
{
    Thread_Carro tmp = list->head;       // Guarda la cabeza en una variable temporal
    if (list->tamanio > 0)              // Verifica que la lista no este vacia
    {
        list->head = tmp->next;         // Cambia la cabeza al elemento siguiente
        tmp->next = NULL;               // Elimina la relacion de siguiente de la cabeza anterior con la actual.

        if (list->head != NULL)         // Verifica si la cabeza nueva no sea vacia
        {
            list->head->prev = NULL;    // Elimina la relacion de anterior de la nueva cabeza con la vieja.
        }

        // Valida si el tipo de carro es ambulacia o radioactivo para disminuir la cantidad de la lista
        switch(tmp->tipo_carro)
        {
        case 1  :
            list->cantidad_ambulancias -= 1;
            break;

        case 2  :
            list->cantidad_radioactivos -= 1;
            break;
        }

        // Disminuye la cantidad de elementos de la lista.
        list->tamanio -=1;
    }
    return tmp;
}


/**
 * Agrega el elemento a la lista
 */
void agregar_carro_prioridad(Thread_Carro node, ThreadListCarro list)
{
    //Envejecer(list);
    //printf("\n\n\n*** Insertando nodo: %d *** tam %d",node->thread_identificador,list->tamanio);
    if (list->head == NULL)
    {
        //printf("\nINSERTO PRIMER ELEMETO");
        list->head = node;
        list->tail = node;
        list->tamanio += 1;
        //sleep(5);
    }
    else
    {
        Thread_Carro tmp = list->head;
        int flag = 0;

        while (tmp != NULL && flag == 0)
        {
            //printf("\n** Revisando tmp: %d Prioridad: %d **\n",tmp->thread_identificador,tmp->prioridad);
            //printf("** Revisando Nodo: %d Prioridad: %d **\n",node->thread_identificador,node->prioridad);
            //sleep(1);

            //Prioridad es mayor al nodo en evaluacion
            if (node->prioridad < tmp->prioridad)
            {
                //printf("\nTiene prioridad mayor");
                //Nodo es la cabeza
                if(tmp->thread_identificador ==  list->head->thread_identificador)
                {
                    //printf("\nPrioridad mayor a Cabeza");
                    node->next = list->head;        //Apunta el siguiente del nodo a la cabeza de la lista
                    list->head->prev = node;        //Apunta el anterior de la cabeza al nodo
                    list->head = node;              //Corre el de la cabeza al nodo nuevo
                }
                else
                {
                    //Insercion intermedia
                    //printf("\nPrioridad mayor a (%d,%d)",tmp->thread_identificador,tmp->prioridad);
                    tmp->prev->next = node;     //Nodo anterior al tmp se le asigna como el siguiente el nodo entrante
                    node->next = tmp;
                    node->prev = tmp->prev;           //
                    tmp->prev = node;
                }
                list->tamanio += 1; //Aumenta el tamanio de la lista
                flag = 1;       //Cambia la bandera como ingresado
            }

            tmp = tmp->next;
            //sleep(5);
        }

        //printf("\nFlag: %d",flag);
        if(flag == 0)
        {
            // inserta al final
            //printf("\nInsertando Final de la lista");
            list->tail->next = node;
            node->prev = list->tail;
            list->tail = node;
            list->tamanio += 1;
        }
    }

    switch(node->tipo_carro)
    {
    case AMBULANCIA:
        list->cantidad_ambulancias += 1;
        break;

    case RADIOACTIVO:
        list->cantidad_radioactivos += 1;
        break;
    }

}



void agregar_thread_prioridad(Thread node, ThreadList list)
{
    //Envejecer_Threads(list);
    //printf("\n\n\n*** Insertando nodo: %d *** tam %d",node->thread_identificador,list->tamanio);
    if (list->head == NULL)
    {
        //printf("\nINSERTO PRIMER ELEMETO");
        list->head = node;
        list->tail = node;
        list->tamanio += 1;
        //sleep(5);
    }
    else
    {
        Thread tmp = list->head;
        int flag = 0;

        while (tmp != NULL && flag == 0)
        {
            //printf("\n** Revisando tmp: %d Prioridad: %d **\n",tmp->thread_identificador,tmp->prioridad);
            //printf("** Revisando Nodo: %d Prioridad: %d **\n",node->thread_identificador,node->prioridad);
            //sleep(1);

            //Prioridad es mayor al nodo en evaluacion
            if (node->prioridad < tmp->prioridad)
            {
                //printf("\nTiene prioridad mayor");
                //Nodo es la cabeza
                if(tmp->thread_identificador ==  list->head->thread_identificador)
                {
                    //printf("\nPrioridad mayor a Cabeza");
                    node->next = list->head;        //Apunta el siguiente del nodo a la cabeza de la lista
                    list->head->prev = node;        //Apunta el anterior de la cabeza al nodo
                    list->head = node;              //Corre el de la cabeza al nodo nuevo
                }
                else
                {
                    //Insercion intermedia
                    //printf("\nPrioridad mayor a (%d,%d)",tmp->thread_identificador,tmp->prioridad);
                    tmp->prev->next = node;     //Nodo anterior al tmp se le asigna como el siguiente el nodo entrante
                    node->next = tmp;
                    node->prev = tmp->prev;           //
                    tmp->prev = node;
                }
                list->tamanio += 1; //Aumenta el tamanio de la lista
                flag = 1;       //Cambia la bandera como ingresado
            }

            tmp = tmp->next;
            //sleep(5);
        }

        //printf("\nFlag: %d",flag);
        if(flag == 0)
        {
            // inserta al final
            //printf("\nInsertando Final de la lista");
            list->tail->next = node;
            node->prev = list->tail;
            list->tail = node;
            list->tamanio += 1;
        }
    }

}



void agregar_thread_velocidad(Thread node, ThreadList list)
{
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        list->tamanio += 1;
    }
    else
    {
        Thread tmp = list->head;
        int flag = 0;

        while (tmp != NULL && flag == 0)
        {
            //Prioridad es mayor al nodo en evaluacion
            if (node->velocidad > tmp->velocidad)
            {
                //Nodo es la cabeza
                if(tmp->thread_identificador ==  list->head->thread_identificador)
                {
                    node->next = list->head;        //Apunta el siguiente del nodo a la cabeza de la lista
                    list->head->prev = node;        //Apunta el anterior de la cabeza al nodo
                    list->head = node;              //Corre el de la cabeza al nodo nuevo
                }
                else
                {
                    //Insercion intermedia
                    tmp->prev->next = node;     //Nodo anterior al tmp se le asigna como el siguiente el nodo entrante
                    node->next = tmp;
                    node->prev = tmp->prev;           //
                    tmp->prev = node;
                }
                list->tamanio += 1; //Aumenta el tamanio de la lista
                flag = 1;       //Cambia la bandera como ingresado
            }

            tmp = tmp->next;
        }

        if(flag == 0)
        {
            // inserta al final
            list->tail->next = node;
            node->prev = list->tail;
            list->tail = node;
            list->tamanio += 1;
        }
    }

}









///////////////////////////////////////////////////

/**
 * Agrega el nodo Thread al final de la lista por ser un puente
 */
void agregar_Puente_Tiempo_Real(Thread node, ThreadList list)
{
    if(list->head == NULL)
    {
        list->head = node;  // Define al nodo como cabeza
        list->tail = node;  // Define al nodo como cola
    }
    else
    {
        ((Thread)list->tail)->next = node; // Define el elemento siguiente del tail hacia el nuevo nodo
        node->prev = ((Thread)list->tail); // Define el elemento anterior del nodo nuevo hacia el tail de la lista
        list->tail = node;                         // Cambia el puntero tail al nodo nuevo
    }
}


/**
 * Ingresa los carros por orden de velocidad, a mayor velocidad ira mas adelante en la lista.
 */
void agregar_Carro_Tiempo_Real_Lista_General(Thread node, ThreadList list)
{
    //printf("\n++ Insertando Carro ++");

    //printf("Tam %d\n",list->tamanio);
    //printf("\nHILO : %lu",list->head->puente->puente_id);

    if (list->head == NULL)
    {
        //printf("\nINSERTO PRIMER ELEMENTO");
        list->head = node;
        list->tail = node;
    }
    else
    {
        //printf("\n\n-- BUSCANDO --");
        Thread tmp = list->head;
        int flag = 0;

        while (tmp != NULL && flag == 0)
        {
            if(tmp->puente == NULL)
            {
                Thread_Carro carroLista = tmp->carro;
                Thread_Carro carroNuevo = node->carro;

                //printf("\n** (TMP) Codigo: %d, Tipo Carro: %d, Velocidad: %d **\n",carroLista->thread_identificador,carroLista->tipo_carro,carroLista->velocidad);
                //printf("** (NUEVO) Codigo: %d, Tipo Carro: %d, Velocidad: %d **\n",carroNuevo->thread_identificador,carroNuevo->tipo_carro,carroNuevo->velocidad);
                //sleep(1);

                //Prioridad es mayor al nodo en evaluacion
                if (  carroNuevo->tipo_carro >= carroLista->tipo_carro && carroNuevo->velocidad > carroLista->velocidad )
                {
                    //printf("\n-- INGRESANDO --");
                    //Nodo es la cabeza
                    if(tmp->thread_identificador ==  list->head->thread_identificador)
                    {
                        //printf("\nCABEZA");
                        node->next = list->head;        //Apunta el siguiente del nodo a la cabeza de la lista
                        list->head->prev = node;        //Apunta el anterior de la cabeza al nodo
                        list->head = node;              //Corre el de la cabeza al nodo nuevo
                    }
                    else
                    {
                        //Insercion intermedia
                        //printf("\nINTERMEDIO");
                        tmp->prev->next = node;     //Nodo anterior al tmp se le asigna como el siguiente el nodo entrante
                        node->next = tmp;
                        node->prev = tmp->prev;           //
                        tmp->prev = node;
                    }
                    flag = 1;       //Cambia la bandera como ingresado
                }
            }
            tmp = tmp->next;
            //sleep(1);
        }

        //printf("\nFlag: %d",flag);
        if(flag == 0)
        {
            // inserta al final
            //printf("\nFINAL");
            list->tail->next = node;
            node->prev = list->tail;
            list->tail = node;
        }
    }

}

/**
 * Ingresa a la lista los carros tomando en cuanta distintos criterios. Primer criterio que valida es que si
 * el tipo (Radioactivo -> 2, Ambulacia -> 1, Carro -> 0) es superior. Luego de esto si ambos son radioactivos se
 * basa en el criterio del tiempo el que tenga menor tiempo. En caso de que ambos tengan el mismo tiempo el mas veloz
 * sera el que tenga prioridad
 */
void agregar_Radioactivo_Tiempo_Real_Lista_General (Thread node, ThreadList list)
{
    //printf("\n++ Insertando Radioactivo ++");
    if (list->head == NULL)
    {
        //printf("\nINSERTO PRIMER ELEMENTO");
        list->head = node;
        list->tail = node;
        //sleep(1);
    }
    else
    {
        Thread tmp = list->head;
        int flag = 0;

        while (tmp != NULL && flag == 0)
        {
            if(tmp->puente == NULL)
            {
                Thread_Carro carroLista = tmp->carro;
                Thread_Carro carroNuevo = node->carro;
                //printf("\n** (TMP) Codigo: %d, Tipo Carro: %d, Velocidad: %d Tiempo: %d**\n", carroLista->thread_identificador, carroLista->tipo_carro,carroLista->velocidad, carroLista->limite_tiempo);
                //printf("\n** (NODE) Codigo: %d, Tipo Carro: %d, Velocidad: %d Tiempo: %d**\n", carroNuevo->thread_identificador, carroNuevo->tipo_carro, carroNuevo->velocidad, carroNuevo->limite_tiempo);
                //sleep(1);

                int esTipoMayor      = (carroNuevo->tipo_carro    >   carroLista->tipo_carro)    ? 1 : 0;
                int esTipoIgual      = (carroNuevo->tipo_carro    ==  carroLista->tipo_carro)    ? 1 : 0;
                int esTiempoMenor    = (carroNuevo->limite_tiempo <   carroLista->limite_tiempo) ? 1 : 0;
                int esTiempoIgual    = (carroNuevo->limite_tiempo ==  carroLista->limite_tiempo) ? 1 : 0;
                int esVelocidadMayor = (carroNuevo->velocidad     >   carroLista->velocidad)     ? 1 : 0;

                //Prioridad es mayor al nodo en evaluacion
                if ( esTipoMayor == 1 || ( esTipoIgual == 1 && ( esTiempoMenor == 1 || ( esTiempoIgual == 1 && esVelocidadMayor == 1 ) ) ) )
                {
                    //printf("\n-- INGRESANDO --");
                    //Nodo es la cabeza
                    if(tmp->thread_identificador ==  list->head->thread_identificador)
                    {
                        //printf("\nCABEZA");
                        node->next = list->head;        //Apunta el siguiente del nodo a la cabeza de la lista
                        list->head->prev = node;        //Apunta el anterior de la cabeza al nodo
                        list->head = node;              //Corre el de la cabeza al nodo nuevo
                    }
                    else
                    {
                        //Insercion intermedia
                        //printf("\nINTERMEDIO");
                        tmp->prev->next = node;     //Nodo anterior al tmp se le asigna como el siguiente el nodo entrante
                        node->next = tmp;
                        node->prev = tmp->prev;           //
                        tmp->prev = node;
                    }
                    flag = 1;       //Cambia la bandera como ingresado
                }
            }
            tmp = tmp->next;
            //sleep(1);
        }

        //printf("\nFlag: %d",flag);
        if(flag == 0)
        {
            // inserta al final
            //printf("\nFINAL");
            list->tail->next = node;
            node->prev = list->tail;
            list->tail = node;
        }
    }
}

void agregar_Ambulacia_Tiempo_Real_Lista_General(Thread node, ThreadList list)
{
    //printf("\n++ Insertando Ambulancia ++");
    if (list->head == NULL)
    {
        //printf("\nINSERTO PRIMER ELEMETO");
        list->head = node;
        list->tail = node;
    }
    else
    {
        Thread tmp = list->head;

        int flag = 0;

        while (tmp != NULL && flag == 0)
        {
            if(tmp->puente == NULL)
            {
                Thread_Carro carroLista = tmp->carro;
                Thread_Carro carroNuevo = node->carro;

                //printf("\n** (TMP) Codigo: %d, Tipo Carro: %d, Velocidad: %d **\n",carroLista->thread_identificador,carroLista->tipo_carro,carroLista->velocidad);
                //printf("** (NUEVO) Codigo: %d, Tipo Carro: %d, Velocidad: %d **\n",carroNuevo->thread_identificador,carroNuevo->tipo_carro,carroNuevo->velocidad);
                //sleep(1);

                //Prioridad es mayor al nodo en evaluacion
                if ( (carroNuevo->tipo_carro > carroLista->tipo_carro) || (carroNuevo->tipo_carro == carroLista->tipo_carro && carroNuevo->velocidad > carroLista->velocidad) )
                {
                    //printf("\n-- INGRESANDO --");
                    //Nodo es la cabeza
                    if(tmp->thread_identificador ==  list->head->thread_identificador)
                    {
                        //printf("\nCABEZA");
                        node->next = list->head;        //Apunta el siguiente del nodo a la cabeza de la lista
                        list->head->prev = node;        //Apunta el anterior de la cabeza al nodo
                        list->head = node;              //Corre el de la cabeza al nodo nuevo
                    }
                    else
                    {
                        //Insercion intermedia
                        //printf("\nINTERMEDIO");
                        tmp->prev->next = node;     //Nodo anterior al tmp se le asigna como el siguiente el nodo entrante
                        node->next = tmp;
                        node->prev = tmp->prev;           //
                        tmp->prev = node;
                    }
                    flag = 1;       //Cambia la bandera como ingresado
                }
            }
            tmp = tmp->next;
            //sleep(1);
        }

        //printf("\nFlag: %d",flag);
        if(flag == 0)
        {
            // inserta al final
            //printf("\nFINAL");
            list->tail->next = node;
            node->prev = list->tail;
            list->tail = node;
        }
    }
}

void agregar_thread_Tiempo_Real(Thread node, ThreadList list)
{

    if(node->thread_identificador < 4)
    {
        printf("\n\n//// INSERTANTO PUENTE \\\\");
        agregar_Puente_Tiempo_Real(node, list);
    }
    else
    {
        printf("\n\n//// INSERTANTO CARRO \\\\");
        Thread_Carro carro = node->carro;      // asigna nodo para manejarlo como carro

        //printf("\nINSERTAR CARRO\n");
        //agregar_Carro_Tiempo_Real_Lista_General(node,list);

        switch(carro->tipo_carro)
        {
        case 1  :
            printf("\nINSERTAR AMBULACIA\n");
            agregar_Ambulacia_Tiempo_Real_Lista_General(node,list);
            break;

        case 2  :
            printf("\nINSERTAR RADIOACTIVO\n");
            agregar_Radioactivo_Tiempo_Real_Lista_General(node,list);
            break;

        default:
            printf("\nINSERTAR CARRO\n");
            agregar_Carro_Tiempo_Real_Lista_General(node,list);
            break;
        }
    }
    list->tamanio +=1;
}

///////////////////////////////////////////////////





/*
void agregar_carro_velocidad(Thread_Carro node, ThreadListCarro list)
{
    if (list->head == NULL)
    {
        list->head = node;
        list->tail = node;
        list->tamanio += 1;
    }
    else
    {
        Thread_Carro tmp = list->head;
        int flag = 0;

        while (tmp != NULL && flag == 0)
        {
            //Prioridad es mayor al nodo en evaluacion
            if (node->velocidad < tmp->velocidad)
            {
                //Nodo es la cabeza
                if(tmp->thread_identificador ==  list->head->thread_identificador)
                {
                    node->next = list->head;        //Apunta el siguiente del nodo a la cabeza de la lista
                    list->head->prev = node;        //Apunta el anterior de la cabeza al nodo
                    list->head = node;              //Corre el de la cabeza al nodo nuevo
                }
                else
                {
                    //Insercion intermedia
                    tmp->prev->next = node;     //Nodo anterior al tmp se le asigna como el siguiente el nodo entrante
                    node->next = tmp;
                    node->prev = tmp->prev;           //
                    tmp->prev = node;
                }
                list->tamanio += 1; //Aumenta el tamanio de la lista
                flag = 1;       //Cambia la bandera como ingresado
            }

            tmp = tmp->next;
        }

        if(flag == 0)
        {
            // inserta al final
            list->tail->next = node;
            node->prev = list->tail;
            list->tail = node;
            list->tamanio += 1;
        }
    }

    switch(node->tipo_carro)
    {
    case 1  :
        list->cantidad_ambulancias += 1;
        break;

    case 2  :
        list->cantidad_radioactivos += 1;
        break;
    }

}*/

