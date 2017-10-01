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

       switch(node->tipo_carro) {
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

Thread pop_primer_thread(ThreadList list){
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

Thread_Puente buscar_nodo_puente(ThreadListPuente list, long thread_identificador){
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
                        Thread_Carro tmp2 = tmp->next;
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
 * Aumenta en una unidad la prioridad de cada elemento de la lista.
 */
void Envejecer(ThreadListCarro list){
    Thread_Carro tmp = list->head;
    int largo = list->tamanio;
    for (int indice = 0; indice < largo; indice++){
        //printf("Identificador: %d \t",tmp->thread_identificador);
        //printf("\nPrioridad: %d \n",tmp->prioridad);
        tmp->prioridad += 1;
        tmp = tmp->next;
    }
}

/**
 * Elimina la cabeza de la lista como parametro.
 */
Thread_Carro popCar(ThreadListCarro list){
    Thread_Carro tmp = list->head;       // Guarda la cabeza en una variable temporal
    if (list->tamanio > 0) {            // Verifica que la lista no este vacia
        list->head = tmp->next;         // Cambia la cabeza al elemento siguiente
        tmp->next = NULL;               // Elimina la relacion de siguiente de la cabeza anterior con la actual.

        if (list->head != NULL) {       // Verifica si la cabeza nueva no sea vacia
            list->head->prev = NULL;    // Elimina la relacion de anterior de la nueva cabeza con la vieja.
        }

        // Valida si el tipo de carro es ambulacia o radioactivo para disminuir la cantidad de la lista
        switch(tmp->tipo_carro) {
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
void agregar_thread_priority(Thread_Carro node, ThreadListCarro list)
{
    Envejecer(list);
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

        while (tmp != NULL && flag == 0){
        //printf("\n** Revisando tmp: %d Prioridad: %d **\n",tmp->thread_identificador,tmp->prioridad);
        //printf("** Revisando Nodo: %d Prioridad: %d **\n",node->thread_identificador,node->prioridad);
        //sleep(1);

            //Prioridad es mayor al nodo en evaluacion
            if (node->prioridad > tmp->prioridad){
                //printf("\nTiene prioridad mayor");
                //Nodo es la cabeza
                if(tmp->thread_identificador ==  list->head->thread_identificador){
                    //printf("\nPrioridad mayor a Cabeza");
                    node->next = list->head;        //Apunta el siguiente del nodo a la cabeza de la lista
                    list->head->prev = node;        //Apunta el anterior de la cabeza al nodo
                    list->head = node;              //Corre el de la cabeza al nodo nuevo
                }else{
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
        if(flag == 0){
            // inserta al final
            //printf("\nInsertando Final de la lista");
            list->tail->next = node;
            node->prev = list->tail;
            list->tail = node;
            list->tamanio += 1;
        }
    }

    switch(node->tipo_carro) {
    case AMBULANCIA:
        list->cantidad_ambulancias += 1;
        break;

    case RADIOACTIVO:
        list->cantidad_radioactivos += 1;
        break;
    }

}
